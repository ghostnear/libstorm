#include "system/AssetManager.hpp"

namespace Storm
{
    AssetType getAssetTypeFromName(std::string name)
    {
        if(name == "font")
            return AssetType::Font;
        return AssetType::Unknown;
    }

    void FontAsset::load(AssetToLoad metadata)
    {
        _path = metadata.path;
        if(metadata.args)
        {
            json* args = (json*)metadata.args;
            
            // No sizes are loaded yet so getting should load them on the fly.
            if((*args)["sizes"].is_array())
                for(auto x : (*args)["sizes"])
                    get(x);
                
            delete args;
        }
    }

    #define theLoader AssetLoader::getInstance()

    void AssetLoader::start()
    {
        // Can't start an already started thread
        if(theLoader._t != nullptr)
            return;
        theLoader._t = new std::thread(AssetLoader::doAssetLoading);
    }

    void AssetLoader::finish()
    {
        // Can't join an unstarted thread
        if(theLoader._t == nullptr)
            return;
        theLoader._t->join();
        delete theLoader._t;
        theLoader._t = nullptr;
    }

    AssetLoader& AssetLoader::getInstance()
    {
        static AssetLoader instance;
        return instance;
    }

    void AssetLoader::reset()
    {
        theLoader._maxCount = 0;
    }

    double AssetLoader::getPercentage()
    {
        if(AssetLoader::getCount() == 0)
            return 1;
        return 1.0 - (1.0 * AssetLoader::getCount() / AssetLoader::getMaxCount());
    }

    size_t AssetLoader::getCount()
    {
        return theLoader._q.size();
    }

    size_t AssetLoader::getMaxCount()
    {
        return theLoader._maxCount;
    }

    void AssetLoader::doAssetLoading()
    {
        // Do the loading while the queue is not empty, do it at a rate of max 1000 assets per sec
        // (should be way more than enough) until I find a way to deal with this (TODO btw)
        while(!theLoader._q.empty() && !Window::shouldClose())
        {
            AssetToLoad currentAsset = theLoader._q.front();
            theLoader._q.pop();

            // Load the asset based on type
            Asset* newAsset;
            switch(currentAsset.type)
            {
                case AssetType::Font:
                    newAsset = new FontAsset();
                    break;
                    
                default:
                    // Ignore
                    break;
            }
            newAsset->load(currentAsset);
            AssetManager::saveAsset(newAsset, currentAsset.name);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
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
                    // TODO: check if path actually exists
                    load(pathWithoutFilename + assetJSON["path"].get<std::string>());
                }
                // General loading
                else
                {
                    // Push the asset to the loading thread.
                    AssetToLoad newAsset;
                    newAsset.type = getAssetTypeFromName(assetJSON["type"].get<std::string>());
                    newAsset.name = assetJSON["name"].get<std::string>();
                    newAsset.path = pathWithoutFilename + assetJSON["path"].get<std::string>();
                    newAsset.args = (void*)new json(assetJSON["data"]);
                    // ! Make sure to delete this in the loading thread for the asset type !
                    theLoader._q.push(newAsset);
                    theLoader._maxCount += 1;
                }
            }
            else
                showSimpleMessageBox("Error", "Invalid asset reading at JSON descriptor from path: " + path, SDL_MESSAGEBOX_ERROR, Window::getInstance().getSDL());
        }
    }
    
    #undef theLoader
};
