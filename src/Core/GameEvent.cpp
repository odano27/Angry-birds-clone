#include "GameEvent.h"

void GameEventBus::Publish(GameEvent event, bool force) {
  if (force)
    ProcessEvent(event);
  else
    _events.push(event);
}

void GameEventBus::AddEventHandler(GameEvent::EventType eventType,
                                   IGameEventHandler* handler) {
  _eventHandlers.insert(std::make_pair(eventType, handler));
}

void GameEventBus::ProcessEvents() {
  GameEvent event;
  while (PollEvent(event)) ProcessEvent(event);
}

void GameEventBus::ProcessEvent(const GameEvent& event) {
  auto range = _eventHandlers.equal_range(event.type);
  for (auto it = range.first; it != range.second; ++it)
    it->second->HandleGameEvent(event);
}

bool GameEventBus::PollEvent(GameEvent& event) {
  if (_events.empty()) return false;
  event = _events.front();
  _events.pop();
  return true;
}
