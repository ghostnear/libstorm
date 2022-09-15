#ifndef LIBSTORM_ASSET_MANAGER_HPP
#define LIBSTORM_ASSET_MANAGER_HPP

#include "deps.hpp"
#include "external/nlohmann_json.hpp"
#include <map>
#include <memory>

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

    class AssetManager
    {
    public:
        // Asset handling
        template<typename T> void saveAsset(T* assetPointer, std::string identifier)    {   _assetMap[identifier] = assetPointer;   }
        template<typename T> T* getAsset(std::string identifier)    {   return (T*)_assetMap[identifier];   }

        // Getters / Setters
        std::string getMessage()    {   return _m;  }

        // Loads a JSON descriptor, adding the assets to the queue.
        // The queue gets loaded on a separate thread.
        void load(std::string path);
    private:
        std::map<std::string, Asset*> _assetMap;
        std::string _m = "Not loading.";
        std::thread* _t = nullptr;
    };
};

#endif
