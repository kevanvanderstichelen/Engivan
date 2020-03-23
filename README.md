# Intro (Game Engine)

TBA

# Intro (Game Bubble Bobble)
 ![Version 0.2](https://i.imgur.com/CWmTs0M.jpg)

# Versions

 **1. [Version 0.1]**
- ADDED: Sprite, Text & Transform components
- ADDED: FPS counter (GameTime.h/cpp)
- ADDED: Devlogger (DEBUG only) - printing warnings, errors ...
- FIX: Game loop

 **2. [Version 0.2]**
- ADDED: Game Project
- ADDED: Audio Files ( AudioManager, SoundEffect, SoundStream (Music) ) You can Provide() a Audio service (ex. LoggedAudio class)
- ADDED: Input Manager (Full Control Buttons & joystick axis + viberation options + Multiple controllers option )
- ADDED: Scene.h & .cpp (Instead of smart pointers now raw for performance )
- ADDED: TransformComponent.h/.cpp Translate options
- ADDED: FVector2 & FVector3 typedef instead of glm::vec2.
- ADDED: BubbleBobbleScene with playing music at start and left joystick axis as demo.
- ADDED: Command.h Base class, used for assigning commands to specific buttons @ InputManager
