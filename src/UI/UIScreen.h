#pragma once

#include "AssetLoader.h"
#include "UIElement.h"

enum class UIScreenType {
  MainMenu,
  HUD,
};

class IUIManager;

class UIScreen {
 public:
  UIScreen(const Vector2& globalPosition, IUIManager& manager);
  virtual ~UIScreen() {}

  void HandleClick(const Vector2& screenPosition);
  void Draw(Renderer& renderer);

  virtual UIScreenType GetType() = 0;

 protected:
  std::unique_ptr<UIElement> _root;
  IUIManager& _manager;

  void Hide();
  AssetLoader& GetAssets();
};

class IUIManager {
 public:
  friend class UIScreen;

  IUIManager(AssetLoader& assets) : _assets(assets){};
  virtual ~IUIManager() = default;

 protected:
  virtual void PopScreen() = 0;

 private:
  AssetLoader& _assets;
};
