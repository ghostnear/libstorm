#include "system/AssetManager.hpp"
#include "system/AssetTypes/all.hpp"
#include <cstddef>

namespace Storm
{
    AssetType get_asset_type_from_name(std::string name)
    {
        if(name == "font")
            return AssetType::Font;
        if(name == "image")
            return AssetType::Image;
            
        return AssetType::Unknown;
    }

    #define theLoader AssetLoader::get_instance()

    void AssetLoader::start()
    {
        // Can't start an already started thread
        if(theLoader._thread != nullptr)
            return;
        theLoader._thread = new std::thread(AssetLoader::load_assets);
    }

    void AssetLoader::finish()
    {
        // Can't join an unstarted thread
        if(theLoader._thread == nullptr)
            return;
        theLoader._thread->join();
        delete theLoader._thread;
        theLoader._thread = nullptr;
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
        return theLoader._assetQueue.size();
    }

    size_t AssetLoader::get_max_count()
    {
        return theLoader._maxCount;
    }

    void AssetLoader::load_assets()
    {
        // Do the loading while the queue is not empty, at maximum processing speed.
        while(!theLoader._assetQueue.empty() && !Window::should_close())
        {
            AssetToLoad currentAsset = theLoader._assetQueue.front();
            theLoader._assetQueue.pop();

            // Load the asset based on type
            Asset* newAsset = nullptr;
            switch(currentAsset.type)
            {
                case AssetType::Font:
                    newAsset = new FontAsset();
                    break;

                case AssetType::Image:
                    newAsset = new ImageAsset();
                    break;
                    
                default:
                    Window::show_simple_message_box("Error", "Invalid asset type: " + std::to_string(currentAsset.type), SDL_MESSAGEBOX_ERROR);
                    break;
            }

            // Don't explode if the asset is invalid.
            if(newAsset != nullptr)
            {
                newAsset->load(currentAsset);
                AssetManager::save_asset(newAsset, currentAsset.name);
            }
        }
    }

    void AssetLoader::load(std::string path)
    {
        std::ifstream fin(path);

        // If no file, stop and display error
        if(fin.fail())
        {
            Window::show_simple_message_box("Error", "Could not find JSON asset descriptor at path: " + path + "\n", SDL_MESSAGEBOX_ERROR);
            exit(0);
        }

        // Load JSON
        json data = json::parse(fin);
        std::string pathWithoutFilename = Utils::remove_file_name_from_path(path);
        for(auto assetJSON : data)
        {
            if(!assetJSON.is_null())
            {
                try
                {
                    // Recursive load
                    if(assetJSON["type"] == "json")
                        load(pathWithoutFilename + assetJSON["path"].get<std::string>());

                    // General asset loading
                    else
                    {
                        // Push the asset to the loading thread.
                        AssetToLoad newAsset;
                        newAsset.type = get_asset_type_from_name(assetJSON["type"].get<std::string>());
                        newAsset.name = assetJSON["name"].get<std::string>();
                        newAsset.path = pathWithoutFilename + assetJSON["path"].get<std::string>();
                        newAsset.args = (void*)new json(assetJSON["data"]);
                        
                        // ! Make sure to delete this in the loading thread for the asset type !
                        theLoader._assetQueue.push(newAsset);
                        theLoader._maxCount += 1;
                    }
                }
                catch(nlohmann::detail::exception const& e)
                {
                    Window::show_simple_message_box("Error", "Invalid asset at JSON descriptor from path: " + path + "\n" + e.what(), SDL_MESSAGEBOX_ERROR);
                }
            }
            else
                Window::show_simple_message_box("Error", "Invalid asset reading at JSON descriptor from path: " + path, SDL_MESSAGEBOX_ERROR);
        }
    }
    
    #undef theLoader
};
