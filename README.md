## Engine Features
- Level Loader with png/jpg
	* Can load enemies on field with a pixel
	* Reads all pixel of the image
	* Make boxcolliders
	
- Command system
	* Linked with inputManager
- XBOX controller support only (Input Manager)
	* Supports up to 4 Controllers
	* Trigger pressure
	* Buttons (assigned with input manager)
- Finite State machine classes
	* Transition options
	* Stacked state machine
	* Conditions (list)

- Audio Manager
	* SFX support
	* music support
	* play anywhere you want with an ID

- Mini-Physics
	* WorldPhysics.h/cpp
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
