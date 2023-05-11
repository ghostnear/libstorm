#include "deps.hpp"

namespace Utils
{
    SDL_Rect* intersect_rects(SDL_Rect* a, SDL_Rect* b)
    {
        SDL_Rect* result = new SDL_Rect();
        if(SDL_IntersectRect(a, b, result) == SDL_TRUE)
            return result;
        delete result;
        return nullptr;
    }

    json read_json(std::string path)
    {
        std::ifstream file(path);
        json result;
        file >> result;
        file.close();
        return result;
    }

    void write_json(std::string path, json data)
    {
        std::ofstream file(path);
        file << data;
        file.close();
    }

    std::string remove_file_name_from_path(std::string path)
    {
        size_t index = path.size();
        while(index > 0 && path[index] != '/')
            index--;
        return path.substr(0, index + 1);
    }
}