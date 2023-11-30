#pragma once

#include "AssetLoader.h"
#include "GameEvent.h"
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
  GameEventBus& GetEventBus();
  const Vector2& GetWindowSize();
};

class IUIManager {
 public:
  friend class UIScreen;

  IUIManager(GameEventBus& eventBus, AssetLoader& assets, Vector2 windowSize)
      : _eventBus(eventBus), _assets(assets), _windowSize(windowSize){};
  virtual ~IUIManager() = default;

  virtual UIScreen& Show(UIScreenType screenType) = 0;

 protected:
  virtual void PopScreen() = 0;

 private:
  GameEventBus& _eventBus;
  AssetLoader& _assets;
  Vector2 _windowSize;
};
