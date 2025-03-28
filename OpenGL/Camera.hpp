#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include <glad/glad.h>
#include "glm/gtc/matrix_transform.hpp"
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	ASCENT,
	DESCENT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
	private:
		void updateCameraVectors()
		{
			glm::vec3 front;
			front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
			front.y = sin(glm::radians(Pitch));
			front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
			Front = glm::normalize(front);

			Right = glm::normalize(glm::cross(Front, WorldUp));
			Up = glm::normalize(glm::cross(Right, Front));
		}

		glm::mat4 calculate_lookAt_matrix(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
		{
			// 1. Position = known
			// 2. Calculate cameraDirection
			glm::vec3 zaxis = glm::normalize(position - target);
			// 3. Get positive right axis vector
			glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(worldUp), zaxis));
			// 4. Calculate camera up vector
			glm::vec3 yaxis = glm::cross(zaxis, xaxis);

			// Create translation and rotation matrix
			// In glm we access elements as mat[col][row] due to column-major layout
			glm::mat4 translation = glm::mat4(1.0f); // Identity matrix by default
			translation[3][0] = -position.x; // Third column, first row
			translation[3][1] = -position.y;
			translation[3][2] = -position.z;
			glm::mat4 rotation = glm::mat4(1.0f);
			rotation[0][0] = xaxis.x; // First column, first row
			rotation[1][0] = xaxis.y;
			rotation[2][0] = xaxis.z;
			rotation[0][1] = yaxis.x; // First column, second row
			rotation[1][1] = yaxis.y;
			rotation[2][1] = yaxis.z;
			rotation[0][2] = zaxis.x; // First column, third row
			rotation[1][2] = zaxis.y;
			rotation[2][2] = zaxis.z;

			// Return lookAt matrix as combination of translation and rotation matrix
			return rotation * translation; // Remember to read from right to left (first translation then rotation)
		}
	public:
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;

		float Yaw;
		float Pitch;

		float MovementSpeed;
		float MouseSensitivity;
		float Zoom;

		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
			: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
		{
			Position = position;
			WorldUp = up;
			Yaw = yaw;
			Pitch = pitch;
			updateCameraVectors();
			
		}

		Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) 
			: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
		{
			Position = glm::vec3(posX, posY, posZ);
			WorldUp = glm::vec3(upX, upY, upZ);
			Yaw = yaw;
			Pitch = pitch;
			updateCameraVectors();
		}

		glm::mat4 GetViewMatrix()
		{
			return calculate_lookAt_matrix(Position, Position + Front, Up);
		}
		void ProcessKeyboard(Camera_Movement direction, float deltaTime)
		{
			float velocity = MovementSpeed * deltaTime;
			if (direction == FORWARD)
				Position += Front * velocity;
			if (direction == BACKWARD)
				Position -= Front * velocity;
			if (direction == LEFT)
				Position -= Right * velocity;
			if (direction == RIGHT)
				Position += Right * velocity;
			if (direction == ASCENT)
				Position += Up * velocity;
			if (direction == DESCENT)
				Position -= Up * velocity;
		}

		void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
		{
			xoffset *= MouseSensitivity;
			yoffset *= MouseSensitivity;

			Yaw += xoffset;
			Pitch += yoffset;

			if (constrainPitch)
			{
				if (Pitch > 89.0f)
					Pitch = 89.0f;
				if (Pitch < -89.0f)
					Pitch = -89.0f;
			}

			updateCameraVectors();
		}

		void ProcessMouseScroll(float yoffset)
		{
			Zoom -= (float)yoffset;
			if (Zoom < 1.0f)
				Zoom = 1.0f;
			if (Zoom > 45.0f)
				Zoom = 45.0f;
		}

		
};


#endif