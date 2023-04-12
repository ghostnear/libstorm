#include "system/AssetManager.hpp"
#include "system/assetTypes/all.hpp"

namespace Storm
{
    AssetType get_asset_type_from_name(std::string name)
    {
        if(name == "font")
            return AssetType::Font;
        if(name == "sprite")
            return AssetType::Image;
        return AssetType::Unknown;
    }

    #define theLoader AssetLoader::get_instance()

    void AssetLoader::start()
    {
        // Can't start an already started thread
        if(theLoader._t != nullptr)
            return;
        theLoader._t = new std::thread(AssetLoader::load_assets);
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

    AssetLoader& AssetLoader::get_instance()
    {
        static AssetLoader instance;
        return instance;
    }

    void AssetLoader::reset()
    {
        theLoader._maxCount = 0;
    }

    double AssetLoader::get_percentage()
    {
        if(AssetLoader::get_count() == 0)
            return 1;
        return 1.0 - (1.0 * AssetLoader::get_count() / AssetLoader::get_max_count());
    }

    size_t AssetLoader::get_count()
    {
        return theLoader._q.size();
    }

    size_t AssetLoader::get_max_count()
    {
        return theLoader._maxCount;
    }

    void AssetLoader::load_assets()
    {
        // Do the loading while the queue is not empty, do it at a rate of max 1000 assets per sec
        // (should be way more than enough) until I find a way to deal with this (TODO btw)
        while(!theLoader._q.empty() && !Window::should_close())
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

                case AssetType::Image:
                    newAsset = new ImageAsset();
                    break;
                    
                default:
                    // Ignore
                    break;
            }
            newAsset->load(currentAsset);
            AssetManager::save_asset(newAsset, currentAsset.name);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    void AssetLoader::load(std::string path)
    {
        std::ifstream fin(path);

        // If no file, stop and display error
        if(fin.fail())
        {
            show_simple_message_box("Error", "Could not find JSON asset descriptor at path: " + path, SDL_MESSAGEBOX_ERROR, Window::get_instance().get_SDL());
            return;
        }

        // Load JSON
        json data = json::parse(fin);
        std::string pathWithoutFilename = Utils::remove_file_name_from_path(path);
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
                    newAsset.type = get_asset_type_from_name(assetJSON["type"].get<std::string>());
                    newAsset.name = assetJSON["name"].get<std::string>();
                    newAsset.path = pathWithoutFilename + assetJSON["path"].get<std::string>();
                    newAsset.args = (void*)new json(assetJSON["data"]);
                    // ! Make sure to delete this in the loading thread for the asset type !
                    theLoader._q.push(newAsset);
                    theLoader._maxCount += 1;
                }
            }
            else
                show_simple_message_box("Error", "Invalid asset reading at JSON descriptor from path: " + path, SDL_MESSAGEBOX_ERROR, Window::get_instance().get_SDL());
        }
    }
    
    #undef theLoader
};
