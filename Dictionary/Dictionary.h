#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>

class Dictionary {
public:
    void LoadFromFile(const std::string& path);
    std::vector<std::string> Translate(const std::string& word, const std::string& from, const std::string& to) const;
    std::set<std::string> GetLanguages() const;

private:
    // структура: from -> to -> слово -> список значений
    std::map<std::string, std::map<std::string, std::map<std::string, std::vector<std::string>>>> data;
};
