#pragma once

#include <memory>
#include <vector>

#include "Renderer.h"
#include "Vector2.h"

struct UIClickEvent {
  Vector2 screenPosition;
  bool processed;
};

class UIElement {
 public:
  UIElement(const Vector2& localPosition);
  virtual ~UIElement() = default;

  UIElement(const UIElement&) = delete;
  UIElement& operator=(const UIElement&) = delete;

  void AddChild(std::unique_ptr<UIElement> child);
  UIElement& GetChild(int index) const;
  bool PropagateClick(UIClickEvent& event);

  virtual void Draw(Renderer& renderer);
  virtual Vector2 GetGlobalPosition() const;

 protected:
  virtual void OnHierarchyChanged();
  virtual bool CanReceiveClick(const Vector2& screenPosition) const;
  virtual bool TryProcessClick(UIClickEvent& event);

 private:
  Vector2 _localPosition;
  UIElement* _parent;
  std::vector<std::unique_ptr<UIElement>> _childs;

  void SetParent(UIElement* parent);
};
