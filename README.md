## Engine Features
- Level Loader with png/jpg
	* Can load enemies on field with a pixel color
	* Reads all pixel of the image
	* Make boxcolliders
- Resource Manager
	* Load Texture's (with option to TextureFilter's)
	* Load Font's with any size (loaded with .TTF files)
- Command system
	* Linked with inputManager
- XBOX controller support only (Input Manager)
	* Supports up to 4 Controllers
	* Trigger pressure
	* Buttons (assigned with input manager)
	* Vibration settings
- Finite State machine classes
	* Transition options
	* Stacked state machine
	* Conditions (list)
- Audio Manager
	* SFX support
	* music support
	* play anywhere you want with an ID
- Mini-Physics
	* WorldPhysics.h/cpp, checks all boxcolliders collision and apply Minowski difference.
- SceneManager
	* Add any Scene's that is derrived from base class Scene.
	* Can switch scene's
	* Only one active scene at a time. 
- Renderer
	* Draw Point Function (DEBUG ONLY)
	* Draw Lines Function (DEBUG ONLY)
	* Draw Rectangle Function (DEBUG ONLY)
	* Draw Circle Function (DEBUG ONLY)
	* ClearColor options
### Components Features
	* BoxColliderComponent
		* Trigger & Collision CallBacks
		* Static / Dynamic option
		* Automatic scales & size with Sprite component if there is one
	* CameraComponent
		* Add HUD objects
	* FPSComponent
		* On screen fps counter can be actived through macro TIME.ActivateFPSCounter()
	* GridComponent
		* Keeps object between a box grid (default = window size), is adjustable
	* RigidBodyComponent
		* Velocity, Force, Acceleration & Gravity options
	* SpriteComponent
		* Has struct of SpriteAnimation, easy set up more info @ engine
		* Play animation with a string
		* Flip image
		* Add / Remove SpriteAnimation, if not used just static.
	* TextComponent
		* TTF supported, and adjustable sizes
		* Color options
	* TransformComponent
		* SetPosition, Translate(x/y/z) 
		* Rotation
		* Scaling
	* UIComponent (For the game)
		* Made ready for bubble bobble highscore
	* PlayerComponent (For the game)
		* Made ready for bubble bobble
	* HealthComponent (For the game)
		* DoDamage function
		* LinkedObject (To know where it originally came from)
	
- Devlog
	* Print Warnings
	* Print Errors
	* Print Info
	* supports w-string & string

- Colors.h
	* Lot of color codes (based on DirectX lib)


### Game Features
- Audio (Music, and shoot & pickup SFX)
- 3 Level's
- Highscore
- Co-op
- Pickups
- Maita & ZenChan enemy
- XBOX Controller input
- GameCommands.h, All commands of Bubble Bobble
- GameStates.h, All States that are available for Bubble Bobble
