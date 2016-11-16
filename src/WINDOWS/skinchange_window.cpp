#include "skinchange_window.h"

SkinChangerWindow* skinchange_window = nullptr;

SkinChangerWindow::SkinChangerWindow (std::string title, Vector2D size, Vector2D position, Color backgroundColor)
	: Window::Window (title, size, position, backgroundColor, true)
{

  weaponIDTextBox = new TextBox ("Weapon Name", &weaponIDText, LOC(10, 10), LOC(160, 30));
  skinIDTextBox = new TextBox ("Skin ID", &skinIDText, BELOW(weaponIDTextBox), LOC(160, 30));
  seedIDTextBox = new TextBox ("Seed ID", &seedIDText, BELOW(skinIDTextBox), LOC(160, 30));
  wearAmountSlider = new Slider("Wear Amount", STACK(weaponIDTextBox), LOC(160, 30), &wearAmount, 0.005f, 1.0f);
  stattrakTextBox = new TextBox ("Stat Trak", &stattrakText, BELOW(wearAmountSlider), LOC(160, 30));
  nameIDTextBox = new TextBox ("Name Tag", &nameIDText, BELOW(stattrakTextBox), LOC(160, 30));

  setButton = new OutlinedButton ("Set", BELOW(seedIDTextBox), LOC(330, 30));
  setButton->OnClickedEvent = MFUNC (&SkinChangerWindow::ApplySkin, this);

  AddComponent(weaponIDTextBox);
  AddComponent(skinIDTextBox);
  AddComponent(seedIDTextBox);
  AddComponent(wearAmountSlider);
  AddComponent(stattrakTextBox);
  AddComponent(nameIDTextBox);

  AddComponent(setButton);
	Show ();
}

std::string convertToUpper(std::string s)
{
  for (int i = 0; i < s.length(); i++)
    s[i] = toupper(s[i]);
  return s;
}

void SkinChangerWindow::ApplySkin()
{

  for (auto i : Settings::Skinchanger::skins)
	{
    int weaponID = Util::Items::GetItemIndex(convertToUpper(weaponIDText));

    if(weaponID != -1 && i.first == weaponID)
    {
      cvar->ConsoleColorPrintf(ColorRGBA(150, 255, 150), "Wepaon ID: %d\n", weaponID);
      Settings::Skinchanger::skins[i.first] = Settings::Skinchanger::Skin(
        skinIDText.empty() ? -1 : std::stoi(skinIDText),
        -1,
        seedIDText.empty() ? -1 : std::stoi(seedIDText),
        wearAmount,
        stattrakText.empty() ? -1 : std::stoi(stattrakText),
        nameIDText,
        ""
      );
    }
  }
  SkinChanger::ForceFullUpdate = true;
}
