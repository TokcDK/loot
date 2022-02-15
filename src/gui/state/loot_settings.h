/*  LOOT

    A load order optimisation tool for
    Morrowind, Oblivion, Skyrim, Skyrim Special Edition, Skyrim VR,
    Fallout 3, Fallout: New Vegas, Fallout 4 and Fallout 4 VR.

    Copyright (C) 2014 WrinklyNinja

    This file is part of LOOT.

    LOOT is free software: you can redistribute
    it and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.

    LOOT is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with LOOT.  If not, see
    <https://www.gnu.org/licenses/>.
    */

#ifndef LOOT_GUI_STATE_LOOT_SETTINGS
#define LOOT_GUI_STATE_LOOT_SETTINGS

#include <filesystem>
#include <map>
#include <mutex>
#include <optional>
#include <string>
#include <vector>

#include "gui/state/game/game_settings.h"

namespace loot {
std::vector<std::string> checkSettingsFile(
    const std::filesystem::path& filePath);

class LootSettings {
public:
  struct WindowPosition {
    int top{0};
    int bottom{0};
    int left{0};
    int right{0};
    bool maximised{false};
  };

  struct Language {
    std::string locale;
    std::string name;
    std::optional<std::string> fontFamily;
  };

  struct Filters {
    bool hideVersionNumbers{false};
    bool hideCRCs{false};
    bool hideBashTags{true};
    bool hideNotes{false};
    bool hideAllPluginMessages{false};
    bool hideInactivePlugins{false};
    bool hideMessagelessPlugins{false};
  };

  void load(const std::filesystem::path& file,
            const std::filesystem::path& lootDataPath);
  void save(const std::filesystem::path& file);

  bool shouldAutoSort() const;
  bool isDebugLoggingEnabled() const;
  bool updateMasterlist() const;
  bool isLootUpdateCheckEnabled() const;
  std::string getGame() const;
  std::string getLastGame() const;
  std::string getLastVersion() const;
  std::string getLanguage() const;
  std::string getTheme() const;
  std::string getPreludeSource() const;
  std::optional<WindowPosition> getWindowPosition() const;
  const std::vector<GameSettings>& getGameSettings() const;
  const Filters& getFilters() const;
  const std::vector<Language>& getLanguages() const;

  void setDefaultGame(const std::string& game);
  void setLanguage(const std::string& language);
  void setTheme(const std::string& theme);
  void setPreludeSource(const std::string& source);
  void setAutoSort(bool autSort);
  void enableDebugLogging(bool enable);
  void updateMasterlist(bool update);
  void enableLootUpdateCheck(bool enable);

  void storeLastGame(const std::string& lastGame);
  void storeWindowPosition(const WindowPosition& position);
  void storeGameSettings(const std::vector<GameSettings>& gameSettings);
  void storeFilters(const Filters& filters);
  void updateLastVersion();

private:
  bool autoSort_{false};
  bool enableDebugLogging_{false};
  bool updateMasterlist_{true};
  bool enableLootUpdateCheck_{true};
  std::string game_{"auto"};
  std::string lastGame_{"auto"};
  std::string lastVersion_;
  std::string language_{"en"};
  std::string preludeSource_{
      "https://raw.githubusercontent.com/loot/prelude/v0.17/prelude.yaml"};
  std::string theme_{"default"};
  std::optional<WindowPosition> windowPosition_;
  std::vector<GameSettings> gameSettings_{
      GameSettings(GameType::tes3),
      GameSettings(GameType::tes4),
      GameSettings(GameType::tes5),
      GameSettings(GameType::tes5se),
      GameSettings(GameType::tes5vr),
      GameSettings(GameType::fo3),
      GameSettings(GameType::fonv),
      GameSettings(GameType::fo4),
      GameSettings(GameType::fo4vr),
      GameSettings(GameType::tes4, "Nehrim")
          .SetName("Nehrim - At Fate's Edge")
          .SetMaster("Nehrim.esm")
          .SetRegistryKeys({"Software\\Microsoft\\Windows\\CurrentVersion\\"
                            "Uninstall\\Nehr"
                            "im - At Fate's Edge_is1\\InstallLocation",
                            std::string(NEHRIM_STEAM_REGISTRY_KEY)}),
      GameSettings(GameType::tes5, "Enderal")
          .SetName("Enderal: Forgotten Stories")
          .SetRegistryKeys(
              {"HKEY_CURRENT_USER\\SOFTWARE\\SureAI\\Enderal\\Install_Path",
               "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\St"
               "ea"
               "m App 933480\\InstallLocation"})
          .SetGameLocalFolder("enderal")
          .SetMasterlistSource("https://raw.githubusercontent.com/loot/"
                               "enderal/v0.17/masterlist.yaml"),
      GameSettings(GameType::tes5se, "Enderal Special Edition")
          .SetName("Enderal: Forgotten Stories (Special Edition)")
          .SetRegistryKeys(
              {"HKEY_CURRENT_USER\\SOFTWARE\\SureAI\\EnderalSE\\Install_"
               "Path",
               "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\St"
               "ea"
               "m App 976620\\InstallLocation"})
          .SetGameLocalFolder("Enderal Special Edition")
          .SetMasterlistSource("https://raw.githubusercontent.com/loot/"
                               "enderal/v0.17/masterlist.yaml"),
  };
  Filters filters_;
  std::vector<Language> languages_{
      Language({"en", "English", std::nullopt}),
      Language({"bg", "Български", std::nullopt}),
      Language({"cs", "Čeština", std::nullopt}),
      Language({"da", "Dansk", std::nullopt}),
      Language({"de", "Deutsch", std::nullopt}),
      Language({"es", "Español", std::nullopt}),
      Language({"fi", "Suomi", std::nullopt}),
      Language({"fr", "Français", std::nullopt}),
      Language({"it", "Italiano", std::nullopt}),
      Language({"ja", "日本語", "Meiryo"}),
      Language({"ko", "한국어", "Malgun Gothic"}),
      Language({"pl", "Polski", std::nullopt}),
      Language({"pt_BR", "Português do Brasil", std::nullopt}),
      Language({"pt_PT", "Português de Portugal", std::nullopt}),
      Language({"ru", "Русский", std::nullopt}),
      Language({"sv", "Svenska", std::nullopt}),
      Language({"uk_UA", "Українська", std::nullopt}),
      Language({"zh_CN", "简体中文", "Microsoft Yahei"}),
  };

  mutable std::recursive_mutex mutex_;

  void appendBaseGames();
};
}

#endif
