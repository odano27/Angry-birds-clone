#include "UIElement.h"

UIElement::UIElement(const Vector2& localPosition)
    : _localPosition(localPosition), _parent(nullptr) {}

void UIElement::AddChild(std::unique_ptr<UIElement> child) {
  child->SetParent(this);
  _childs.push_back(std::move(child));
}

UIElement& UIElement::GetChild(int index) const { return *_childs.at(index); }

int UIElement::GetChildCount() const { return _childs.size(); }

bool UIElement::PropagateClick(UIClickEvent& event) {
  // Iterate through hierarchy in reverse order until we found the lowest child
  // that can receive a click Try process click while returning back
  for (auto rit = _childs.rbegin(); rit != _childs.rend(); rit++) {
    auto& child = *rit;
    if (child->PropagateClick(event)) {
      if (!event.processed && TryProcessClick(event)) event.processed = true;
      return true;
    }
  }

  if (CanReceiveClick(event.screenPosition)) {
    if (TryProcessClick(event)) event.processed = true;
    return true;
  }
  return false;
}

void UIElement::Draw(Renderer& renderer) {
  for (auto& child : _childs) child->Draw(renderer);
}

Vector2 UIElement::GetGlobalPosition() const {
  if (_parent == nullptr) return _localPosition;
  return _parent->GetGlobalPosition() + _localPosition;
}

void UIElement::OnHierarchyChanged() {
  for (auto& child : _childs) child->OnHierarchyChanged();
}

bool UIElement::CanReceiveClick(const Vector2&) const { return false; }

bool UIElement::TryProcessClick(UIClickEvent&) { return false; }

void UIElement::SetParent(UIElement* parent) {
  _parent = parent;
  OnHierarchyChanged();
}
