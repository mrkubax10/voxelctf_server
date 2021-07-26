#ifndef SRC_WHITELIST_HPP
#define SRC_WHITELIST_HPP
#include <vector>
#include <string>
class Whitelist{
    std::vector<std::string> whitelistData;
    bool enabled;
public:
    Whitelist();
    void addToWhitelist(std::string playerName);
    void removeFromWhitelist(std::string playerName);
    bool isInWhitelist(std::string playerName);
    bool isEnabled();
    void setEnabled(bool enabled);
    std::vector<std::string>& getContent();
    // Loading and saving
    void load();
    void save();
};
#endif