#ifndef LIBSTORM_ASSET_MANAGER_HPP
#define LIBSTORM_ASSET_MANAGER_HPP

#include "deps.hpp"
#include "window.hpp"
#include "external/json.hpp"
#include <fstream>
#include <thread>
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

    // Asset type handler
    enum AssetType
    {
        Unknown = 0,
        Font
    };
    AssetType getAssetTypeFromName(std::string name);

    struct AssetToLoad
    {
        AssetType type;
        std::string name;
        void* args;
    };

    class AssetLoader
    {
        public:
            // Do not allow for multiple instances
            AssetLoader(AssetLoader const&)     = delete;
            void operator=(AssetLoader const&)  = delete;

            // Methods
            static void start();
            static void finish();
            static AssetLoader& getInstance();
            static void reset();
            static double getPercentage();
            static size_t getCount();
            static size_t getMaxCount();

            // Loads a JSON descriptor, adding the assets to the queue.
            // The queue gets loaded on a separate thread.
            static void load(std::string path);

        private:
            static void doAssetLoading();

            // Constructor should be private
            AssetLoader() {}

            // Asset thread
            std::thread* _t = nullptr;

            // Queues for all asset args
            std::queue<AssetToLoad> _q;

            // Queue infos
            size_t _maxCount = 0;
    };
};

#endif
