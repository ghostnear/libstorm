#ifndef LIBSTORM_ASSET_MANAGER_HPP
#define LIBSTORM_ASSET_MANAGER_HPP

#include "deps.hpp"
#include "window.hpp"
#include "external/json.hpp"
#include <fstream>
#include <queue>
#include <unordered_map>
#include <memory>

using json = nlohmann::json;

namespace Storm
{
    // Asset interface
    class Asset {};

    class Font : public Asset
    {
    public:
        // Saves the path of the asset.
        void savePath(std::string path) {   _path = path;   }

        // Gets the font for a specific size.
        TTF_Font* get(size_t size)
        {
            // If it exists, perfect
            if(_f[size])
                return _f[size];

            // Load the font from the path
            _f[size] = TTF_OpenFont(_path.c_str(), size);

            // TODO: log an error if something happened
            // if(!_f[size])

            return _f[size];
        }

        // Frees all sizes.
        void freeAll()
        {
            for(auto x : _f)
                free(x.first);
        }

        // Frees one size.
        void free(size_t size)
        {
            // Don't delete an inexistent font.
            if(!_f[size])
                return;

            TTF_CloseFont(_f[size]);
            _f[size] = nullptr;
        }
    private:
        std::string _path;
        std::map<size_t, TTF_Font*> _f;
    };

    #define assets AssetManager::getInstance()._assetMap

    class AssetManager
    {
        public:
            // Do not allow for multiple instances
            AssetManager(AssetManager const&)   = delete;
            void operator=(AssetManager const&) = delete;

            // Methods
            static AssetManager& getInstance()
            {
                static AssetManager instance;
                return instance;
            }
            template<typename T> static void saveAsset(T* assetPointer, std::string identifier)
            {
                assets[identifier] = assetPointer;
            }
            template<typename T> static T* getAsset(std::string identifier)
            {
                return (T*)assets[identifier];
            }

        private:
            // Constructor should be private
            AssetManager() {}

            // All assets are here
            std::unordered_map<std::string, Asset*> _assetMap;
    };

    #undef assets

    #define assetThread AssetLoader::getInstance()._t
    #define assetCC AssetLoader::getInstance()._currentCount
    #define assetMC AssetLoader::getInstance()._maxCount

    enum AssetType
    {
        Font = 0
    };

    class AssetLoader
    {
        public:
            // Do not allow for multiple instances
            AssetLoader(AssetLoader const&)     = delete;
            void operator=(AssetLoader const&)  = delete;

            // Methods
            static AssetLoader& getInstance()
            {
                static AssetLoader instance;
                return instance;
            }

            // Reset counts
            static void reset()
            {
                assetCC = assetMC = 0;
            }

            // Loads a JSON descriptor, adding the assets to the queue.
            // The queue gets loaded on a separate thread.
            static void load(std::string path)
            {
                std::ifstream fin(path);

                // If no file, stop and display error
                if(fin.fail())
                {
                    showSimpleMessageBox("Error", "Could not find JSON asset descriptor at path: " + path, SDL_MESSAGEBOX_ERROR, Window::getInstance().getSDL());
                    return;
                }

                // Load JSON
                json data = json::parse(fin);
                std::string pathWithoutFilename = Utils::removeFileNameFromPath(path);
                for(auto assetJSON : data)
                {
                    showSimpleMessageBox("Error", assetJSON.dump(), SDL_MESSAGEBOX_ERROR, Window::getInstance().getSDL());
                    if(!assetJSON.is_null())
                    {
                        // Recursive load
                        if(assetJSON["type"] == "json")
                        {
                            // TODO: check if path exists
                            load(pathWithoutFilename + assetJSON["path"].get<std::string>());
                        }
                        // Font loading
                        else if(assetJSON["type"] == "font")
                        {
                            // TODO: Add to queue with args and stuff here
                            // Add the type to _q, the name to _qName, data to _qArgs.

                            // TODO: figure out why this causes an infinite loop??????????
                            //assetMC += 1;
                            //assetCC += 1;
                        }
                    }
                    else
                    {
                        // TODO: throw invalid asset error
                    }
                }
            }

        private:
            // Constructor should be private
            AssetLoader()
            {
                reset();
            }

            // Asset thread
            std::thread* _t = nullptr;

            // Queues for all asset args
            std::queue<AssetType> _q;
            std::queue<std::string> _qName;
            std::queue<void*> _qArgs;

            // Queue infos
            int _currentCount, _maxCount;
    };

    #undef assetThread
};

#endif
