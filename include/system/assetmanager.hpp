#ifndef LIBSTORM_ASSET_MANAGER_HPP
#define LIBSTORM_ASSET_MANAGER_HPP

#include "deps.hpp"
#include <map>
#include <memory>

namespace Storm
{
    // Asset interface
    class Asset {};

    class Font : public Asset
    {
    public:
        void load(std::string path, uint32_t* sizes);
        TTF_Font* get(int size);
    private:
        std::map<uint32_t, TTF_Font*> _f;
    };

    class AssetManager
    {
    public:
        template<typename T>
        T* getAsset(std::string identifier)
        {
            return (T*)_assetMap[identifier];
        }

    private:
        std::map<std::string, Asset*> _assetMap;
    };
};

#endif
