#include "pch.h"
#include "Dictionary.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

void Dictionary::LoadFromFile(const std::string& path) {
    setlocale(LC_ALL, "UTF-8");
    std::ifstream file(path);
    if (!file) throw std::runtime_error("Не удалось открыть словарь: " + path);

    auto pos = path.find_last_of("/\\");
    std::string name = (pos == std::string::npos) ? path : path.substr(pos + 1);
    pos = name.find(" - ");
    if (pos == std::string::npos) throw std::runtime_error("Неверный формат имени словаря: " + path);

    std::string from = name.substr(0, pos);
    std::string to = name.substr(pos + 3);
    to = to.substr(0, to.find('.'));

    std::string line;
    while (std::getline(file, line)) {
        auto dash = line.find(" - ");
        if (dash == std::string::npos) continue;

        std::string key = line.substr(0, dash);
        std::string value = line.substr(dash + 3);
        data[from][to][key].push_back(value);
    }
}

std::vector<std::string> Dictionary::Translate(const std::string& word, const std::string& from, const std::string& to) const {
    auto it1 = data.find(from);
    if (it1 != data.end()) {
        auto it2 = it1->second.find(to);
        if (it2 != it1->second.end()) {
            auto it3 = it2->second.find(word);
            if (it3 != it2->second.end()) {
                // Удалим дубликаты
                std::set<std::string> unique(it3->second.begin(), it3->second.end());
                return std::vector<std::string>(unique.begin(), unique.end());
            }
        }
    }
    return { "Перевод не найден" };
}

std::set<std::string> Dictionary::GetLanguages() const {
    std::set<std::string> langs;
    for (auto it1 = data.begin(); it1 != data.end(); ++it1) {
        const std::string& fromLang = it1->first;
        langs.insert(fromLang);

        const auto& innerMap = it1->second;
        for (auto it2 = innerMap.begin(); it2 != innerMap.end(); ++it2) {
            const std::string& toLang = it2->first;
            langs.insert(toLang);
        }
    }
    return langs;
}