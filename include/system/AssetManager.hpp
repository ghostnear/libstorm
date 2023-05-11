#pragma once

#include "deps.hpp"
#include "Window.hpp"
#include <fstream>
#include <thread>
#include <queue>
#include <unordered_map>
#include <memory>
#include <mutex>

namespace Storm
{
    // Asset type handler
    enum AssetType
    {
        Unknown = 0,
        Font,
        Image,
        Animation
    };
    AssetType get_asset_type_from_name(std::string name);

    struct AssetToLoad
    {
        AssetType type;
        std::string name;
        std::string path;
        void* args;
    };

    // Asset interface
    class Asset
    {
    public:
        virtual void load(AssetToLoad metadata) = 0;
    };

    #define assets AssetManager::get_instance()._assetMap

    class AssetManager
    {
        public:
            // Do not allow for multiple instances
            AssetManager(AssetManager const&)   = delete;
            void operator=(AssetManager const&) = delete;

            // Methods
            static AssetManager& get_instance()
            {
                static AssetManager instance;
                return instance;
            }
            static void save_asset(Asset* assetPointer, std::string identifier)
            {
                std::lock_guard<std::mutex> lock(AssetManager::get_instance()._assetMutex);
                assets[identifier] = assetPointer;
            }
            template<typename T> static T* get_asset(std::string identifier)
            {
                std::lock_guard<std::mutex> lock(AssetManager::get_instance()._assetMutex);
                return (T*)assets[identifier];
            }

        private:
            // Constructor should be private
            AssetManager() {}

            // All assets are here
            std::unordered_map<std::string, Asset*> _assetMap;

            // Mutex for thread safety.
            std::mutex _assetMutex;
    };

    #undef assets

    class AssetLoader
    {
        public:
            // Do not allow for multiple instances
            AssetLoader(AssetLoader const&)     = delete;
            void operator=(AssetLoader const&)  = delete;

            // Methods
            static void start();
            static void finish();
            static AssetLoader& get_instance();
            static void reset();
            static double get_percentage();
            static size_t get_count();
            static size_t get_max_count();

            // Loads a JSON descriptor, adding the assets to the queue.
            // The queue gets loaded on a separate thread.
            static void load(std::string path);

        private:
            static void load_assets();

            // Constructor should be private
            AssetLoader() {}

            // Asset thread
            std::thread* _thread = nullptr;

            // Queues for all asset args
            std::queue<AssetToLoad> _assetQueue;

            // Queue infos
            size_t _maxCount = 0;

            // Mutex for thread safety.
            std::mutex _assetMutex;
    };
};
