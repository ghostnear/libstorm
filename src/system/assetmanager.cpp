#include "system/assetmanager.hpp"

namespace Storm
{
    AssetType getAssetTypeFromName(std::string name)
    {
        if(name == "font")
            return AssetType::Font;
        return AssetType::Unknown;
    }

    #define theLoader AssetLoader::getInstance()
    #define loaderMC theLoader._maxCount
    #define resetLoader theLoader.reset

    AssetLoader& AssetLoader::getInstance()
    {
        static AssetLoader instance;
        return instance;
    }

    void AssetLoader::reset()
    {
        loaderMC = 0;
    }

    double AssetLoader::getPercentage()
    {
        if(AssetLoader::getCount() == 0)
            return 1;
        return 1.0 - (1.0 * AssetLoader::getMaxCount() / AssetLoader::getCount());
    }

    size_t AssetLoader::getCount()
    {
        return theLoader._q.size();
    }

    size_t AssetLoader::getMaxCount()
    {
        return loaderMC;
    }

    void AssetLoader::load(std::string path)
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
            if(!assetJSON.is_null())
            {
                // Recursive load
                if(assetJSON["type"] == "json")
                {
                    // TODO: check if path exists
                    load(pathWithoutFilename + assetJSON["path"].get<std::string>());
                }
                // General loading
                else
                {
                    // Push the asset to the loading thread.
                    theLoader._q.push(getAssetTypeFromName(assetJSON["type"].get<std::string>()));
                    theLoader._qName.push(assetJSON["name"].get<std::string>());
                    json* newPtr = new json(assetJSON["data"]); // Make sure to delete this in the loading thread
                    theLoader._qArgs.push((void*)newPtr);
                    loaderMC += 1;
                }
            }
            else
                showSimpleMessageBox("Error", "Invalid asset reading at JSON descriptor from path: " + path, SDL_MESSAGEBOX_ERROR, Window::getInstance().getSDL());
        }
    }
    
    #undef theLoader
    #undef loaderMC
    #undef resetLoader
};
