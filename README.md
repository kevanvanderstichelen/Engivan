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



 > **[Version 0.6]** ENGINE
- ADDED: WorldPhysics for colliders (cpp & h)
- ADDED: UIComponent.cpp/h, Displaying Highscore for the GAME
- FIXED: Scaling & Rotation now fully working along with other components.
- ADDED: TextComponent TextAllignment option (Left, Center, Right) + Rendering Text now in correct position
- ADDED: SpriteComponent, With insertable Animation, And clip width/height etc...
- FIXED: RootInitialize was never being called ( never passes any initialize function )
- ADDED: RigidbodyComponent, With Forces, Velocity & Acceleration options.
- FIXED: ResourceManager now keeps the Fonts, So manages them instead of components. (leads to memory destructor bugs)
- FIXED: Renderer now supports with aimation, which was not the case previously.
- FIXED: Renderer Drawing lines, Quads etc... Color was not read correctly.
- ADDED: PlayerComponent, Pickup component, HealthComponent, EnemyComponent (Start files)
- ADDED: FRect (Rectangle) structure
- ADDED: InputManager now supports IsControllerPressedDown() & IsControllerConnected()
- FIXED: InputManager minimized useless copy code.
- ADDED: GridComponent, Assign gameobject to keep them between the screen resolution. (Still some tweaking in the future)
- ADDED: FPSComponent, seperate from the GameTime.h singleton class
- ADDED: GameObject Tagging
- ADDED: Devlog, PrintError throws an exception.
- FIXED: Devlog, Converter WString was incorrect
- ADDED: Colors.h More than 100 different colors at your disposal! (works with FColor4) Value 0 - 1.f
- ADDED: BoxColliderComponent, Collision & Trigger options
- ADDED: BoxColliderComponent callback functions (Set the callback function at your disposal.)

- OPTIMIZATION: TextComponent.cpp for rendering text's 
 > **[Version 0.2]** GAME
- ADDED: StartScene Screen ( + Animated logo )
- ADDED: UI, Highscores (not finished yet)
- ADDED: Sprites of Bub ( Idle, shoot, walk ... )
- ADDED: You can move Bub around and jump around. (joystick and mostly Xbox button A)



