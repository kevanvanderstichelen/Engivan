## Intro (Game Engine)

TBA

## Intro (Game Bubble Bobble)
 ![Version 0.2](https://i.imgur.com/CWmTs0M.jpg)

### Versions
 > **[Version 0.1]** ENGINE
- ADDED: Sprite, Text & Transform components
- ADDED: FPS counter (GameTime.h/cpp)
- ADDED: Devlogger (DEBUG only) - printing warnings, errors ...
- FIX: Game loop



 > **[Version 0.2]** ENGINE
- ADDED: Game Project
- ADDED: Audio Files ( AudioManager, SoundEffect, SoundStream (Music) ) You can Provide() a Audio service (ex. LoggedAudio class)
- ADDED: Input Manager (Full Control Buttons & joystick axis + viberation options + Multiple controllers option )
- ADDED: Scene.h & .cpp (Instead of smart pointers now raw for performance )
- ADDED: TransformComponent.h/.cpp Translate options
- ADDED: FVector2 & FVector3 typedef instead of glm::vec2.
- ADDED: Command.h Base class, used for assigning commands to specific buttons @ InputManager
 > **[Version 0.2]** GAME
- ADDED: BubbleBobbleScene with playing music at start and left joystick axis to translate avatar.

 > **[Version 0.3]** ENGINE
- UPDATE: OpenGL Library's (OpenGL Renderer) + SpriteComponent/TextComponent (updated)
- FIXED: Missing/Linker errors of some .lib/include directories
- FIXED: Scaling sprite @ TransformComponent
- ADDED: Main Structs: FColor, FCircle, FRect, FPoint...
- ADDED: Renderer: DrawPoint, DrawLine, DrawRect, DrawCircle functions
- ADDED: StateMachine (Stacked state machine & original )
- ADDED: WorldPhysics.cpp/h
- ADDED: Macro's ENGINE, RENDERER, DEBUGLOG, SCENEMANAGER, GAME -> GetInstance of all those singleton classes. as shortcuts.

 > **[Version 0.3]** GAME
- FIXED: input controller Axis was not reading right.

