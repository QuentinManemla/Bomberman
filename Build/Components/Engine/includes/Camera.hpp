# ifndef CAMERA_HPP
# define CAMERA_HPP

# include <glad/glad.h>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>

# include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	CAMERA_FORWARD,
	CAMERA_BACKWARD,
	CAMERA_LEFT,
	CAMERA_RIGHT,
	CAMERA_UP,
	CAMERA_DOWN,
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class Camera {
	public:
		// Camera Attributes
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;
		// Euler Angles
		float Yaw;
		float Pitch;
		// Camera options
		float MovementSpeed;
		float MouseSensitivity;
		float Zoom;

		// Constructor with vectors
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
			Position = position;
			WorldUp = up;
			Yaw = yaw;
			Pitch = pitch;

			updateCameraVectors();
		}
		// Constructor with scalar values
		Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
		{
			Position = glm::vec3(posX, posY, posZ);
			WorldUp = glm::vec3(upX, upY, upZ);
			Yaw = yaw;
			Pitch = pitch;
			updateCameraVectors();
		}

		Camera(Camera const & src) {
			this->Position = src.Position;
		}
		
		Camera	&operator=(Camera const & rhs) {
			return *(new Camera(rhs));
		}

		~Camera() {}

		void init(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) {
			
			Front = glm::vec3(0.0f, 0.0f, -1.0f);
			MovementSpeed = SPEED;
			MouseSensitivity = SENSITIVITY;
			Zoom = ZOOM;
			
			Position = position;
			WorldUp = up;
			Yaw = yaw;
			Pitch = pitch;

			updateCameraVectors();
		}
		// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
		glm::mat4 GetViewMatrix() {
			return glm::lookAt(Position, Position + Front, Up);
		}

		// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
		void ProcessKeyboard(Camera_Movement direction, float deltaTime) {
			float velocity = MovementSpeed * deltaTime;
			if (direction == CAMERA_FORWARD)
				Position += Front * velocity;
			if (direction == CAMERA_BACKWARD)
				Position -= Front * velocity;
			if (direction == CAMERA_LEFT)
				Position -= Right * velocity;
			if (direction == CAMERA_RIGHT)
				Position += Right * velocity;
			if (direction == CAMERA_UP)
				Position += Up * velocity;
			if (direction == CAMERA_DOWN)
				Position -= Up * velocity;
			updateCameraVectors();
		}
		void DefaultPos() {
			float yoffset = 22.6;
			yoffset *= MouseSensitivity;
			Pitch += yoffset;

			// Update Front, Right and Up Vectors using the updated Euler angles
			updateCameraVectors();
		}
		void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
			xoffset *= MouseSensitivity;
			yoffset *= MouseSensitivity;

			Yaw   += xoffset;
			Pitch += yoffset;

			std::cout << "PITCH :" << yoffset << std::endl;
			// Make sure that when pitch is out of bounds, screen doesn't get flipped
			if (constrainPitch)
			{
				if (Pitch > 89.0f)
					Pitch = 89.0f;
				if (Pitch < -89.0f)
					Pitch = -89.0f;
			}

			// Update Front, Right and Up Vectors using the updated Euler angles
			updateCameraVectors();
		}
	private:
		// Calculates the front vector from the Camera's (updated) Euler Angles
		void updateCameraVectors()
		{
			std::cout << "YAW: " << Yaw << std::endl;
			std::cout << "PITCH: " << Pitch << std::endl;
			// Calculate the new Front vector
			glm::vec3 front;
			front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
			front.y = sin(glm::radians(Pitch)); //54.7502f
			front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
			Front = glm::normalize(front);

			// Also re-calculate the Right and Up vector
			Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
			Up    = glm::normalize(glm::cross(Right, Front));
		}
};

#endif // !CAMERA_HPP
