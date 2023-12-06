#pragma once

#include <b2_body.h>

#include <queue>
#include <unordered_map>

class GameEvent {
 public:
  struct StartLevelEvent {
    int index;
  };

  struct LevelUpdatedEvent {
    int index;
    int enemiesTotal;
    int enemiesDestroyed;
  };

  struct LevelCompletedEvent {
    bool lastLevel;
  };

  enum EventType {
    StartLevel,
    RestartLevel,
    LevelUpdated,
    LevelCompleted,
    NextLevel,
    BackToMenu,
  };

  EventType type;

  union {
    StartLevelEvent startLevel;
    LevelUpdatedEvent levelUpdated;
    LevelCompletedEvent levelCompleted;
  };
};

class IGameEventHandler {
 public:
  virtual ~IGameEventHandler() = default;

  virtual void HandleGameEvent(const GameEvent& event) = 0;
};

class GameEventBus {
 public:
  GameEventBus(){};

  void Publish(GameEvent event, bool force = false);

  void AddEventHandler(GameEvent::EventType eventType,
                       IGameEventHandler* handler);

  void RemoveEventHandler(GameEvent::EventType eventType,
                          IGameEventHandler* handler);

  void ProcessEvents();

 private:
  std::queue<GameEvent> _events;
  std::unordered_multimap<GameEvent::EventType, IGameEventHandler*>
      _eventHandlers;

  void ProcessEvent(const GameEvent& event);

  bool PollEvent(GameEvent& event);
};
