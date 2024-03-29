#pragma once
//implied static
 static const std::vector<float> PLAYER_VERTS = {
		-0.20f, 0.40f, 0.81f, 0.61f, 0.48f, 1.0f,0.20f, 0.40f, 0.81f, 0.61f, 0.48f, 1.0f,-0.20f, 0.40f, 0.81f, 0.61f, 0.48f, 1.0f,-0.20f, 0.40f, 0.81f, 0.61f, 0.48f, 1.0f,-0.60f, 0.0f, 0.81f, 0.61f, 0.48f, 1.0f,-0.20f, 0.20f, 0.81f, 0.61f, 0.48f, 1.0f,
		-0.60f, 0.0f, 0.81f, 0.61f, 0.48f, 1.0f,-0.40f, 0.0f, 0.81f, 0.61f, 0.48f, 1.0f,-0.20f, 0.20f, 0.81f, 0.61f, 0.48f, 1.0f,0.20f, 0.20f, 0.81f, 0.61f, 0.48f, 1.0f,0.40f, 0.0f, 0.81f, 0.61f, 0.48f, 1.0f,0.20f, 0.40f, 0.81f, 0.61f, 0.48f, 1.0f,
		0.20f, 0.40f, 0.81f, 0.61f, 0.48f, 1.0f,0.60f, 0.0f, 0.81f, 0.61f, 0.48f, 1.0f,0.40f, 0.0f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,0.00f, 0.39f, 0.81f, 0.61f, 0.48f, 1.0f,-0.06f, 0.41f, 0.81f, 0.61f, 0.48f, 1.0f,
		-0.06f, 0.41f, 0.81f, 0.61f, 0.48f, 1.0f,-0.12f, 0.44f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,-0.12f, 0.44f, 0.81f, 0.61f, 0.48f, 1.0f,-0.15f, 0.51f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,
		-0.15f, 0.51f, 0.81f, 0.61f, 0.48f, 1.0f,-0.17f, 0.60f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,-0.17f, 0.60f, 0.81f, 0.61f, 0.48f, 1.0f,-0.15f, 0.68f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,
		-0.15f, 0.68f, 0.81f, 0.61f, 0.48f, 1.0f,-0.08f, 0.73f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,-0.08f, 0.73f, 0.81f, 0.61f, 0.48f, 1.0f,-0.02f, 0.74f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,
		-0.02f, 0.74f, 0.81f, 0.61f, 0.48f, 1.0f,0.04f, 0.72f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,0.04f, 0.72f, 0.81f, 0.61f, 0.48f, 1.0f,0.11f, 0.66f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,
		0.11f, 0.66f, 0.81f, 0.61f, 0.48f, 1.0f,0.12f, 0.58f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,0.12f, 0.58f, 0.81f, 0.61f, 0.48f, 1.0f,0.11f, 0.50f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,
		0.11f, 0.50f, 0.81f, 0.61f, 0.48f, 1.0f,0.09f, 0.44f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,0.09f, 0.44f, 0.81f, 0.61f, 0.48f, 1.0f,0.00f, 0.39f, 0.81f, 0.61f, 0.48f, 1.0f,0.0f, 0.61f, 0.81f, 0.61f, 0.48f, 1.0f,
		-0.20f, 0.40f, 1.0f, 0.0f, 0.0f, 1.0f,0.20f, -0.20f, 1.0f, 0.0f, 0.0f, 1.0f,-0.20f, -0.20f, 1.0f, 0.0f, 0.0f, 1.0f,0.20f, -0.20f, 1.0f, 0.0f, 0.0f, 1.0f,0.20f, 0.40f, 1.0f, 0.0f, 0.0f, 1.0f,-0.20f, 0.40f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.20f, -0.20f, 0.0f, 0.0f, 1.0f, 1.0f,-0.40f, -0.80f, 0.0f, 0.0f, 1.0f, 1.0f,-0.20f, -0.80f, 0.0f, 0.0f, 1.0f, 1.0f,-0.20f, -0.80f, 0.0f, 0.0f, 1.0f, 1.0f,0.0f, -0.20f, 0.0f, 0.0f, 1.0f, 1.0f,-0.20f, -0.20f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.20f, -0.80f, 0.0f, 0.0f, 1.0f, 1.0f,0.0f, -0.20f, 0.0f, 0.0f, 1.0f, 1.0f,0.20f, -0.20f, 0.0f, 0.0f, 1.0f, 1.0f,0.20f, -0.20f, 0.0f, 0.0f, 1.0f, 1.0f,0.40f, -0.80f, 0.0f, 0.0f, 1.0f, 1.0f,0.20f, -0.80f, 0.0f, 0.0f, 1.0f, 1.0f
};

 const std::vector<float> ENEMY1_VERTS = {
			0.0f, 0.00f, 1.0f, 0.09f, 0.0f, 1.0f,
			0.20f, 0.20f, 1.0f, 0.09f, 0.0f, 1.0f,
		   -0.20f, 0.20f, 1.0f, 0.09f, 0.0f, 1.0f,
			0.0f, 0.00f, 0.45f, 0.0f, 0.55f, 1.0f,
			0.0f, -0.40f, 0.45f, 0.0f, 0.55f, 1.0f,
		   -0.20f, 0.20f, 0.45f, 0.0f, 0.55f, 1.0f,
			0.0f, 0.00f, 0.45f, 0.0f, 0.55f, 1.0f,
			0.0f, -0.40f, 0.45f, 0.0f, 0.55f, 1.0f,
			0.20f, 0.20f, 0.45f, 0.0f, 0.55f, 1.0f,
			0.20f, 0.20f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.40f, 0.00f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, -0.40f, 1.0f, 0.0f, 0.0f, 1.0f,
		   -0.20f, 0.20f, 1.0f, 0.0f, 0.0f, 1.0f,
		   -0.40f, 0.00f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, -0.40f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.40f, 0.00f, 0.45f, 0.0f, 0.55f, 1.0f,
			0.60f, -0.40f, 0.45f, 0.0f, 0.55f, 1.0f,
			0.0f, -0.40f, 0.45f, 0.0f, 0.55f, 1.0f,
		   -0.40f, 0.00f, 0.45f, 0.0f, 0.55f, 1.0f,
		   -0.60f, -0.40f, 0.45f, 0.0f, 0.55f, 1.0f,
			0.0f, -0.40f, 0.45f, 0.0f, 0.55f, 1.0f,
		   -0.60f, -0.40f, 1.0f, 0.0f, 0.0f, 1.0f,
		   -0.60f, -0.60f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, -0.40f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, -0.40f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.60f, -0.60f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.60f, -0.40f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.60f, -0.60f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, -0.40f, 1.0f, 0.0f, 0.0f, 1.0f,
		   -0.60f, -0.60f, 1.0f, 0.0f, 0.0f, 1.0f,
		   -0.60f, -0.60f, 0.0f, 1.0f, 0.0f, 1.0f,
		   -0.40f, -0.80f, 0.0f, 1.0f, 0.0f, 1.0f,
		   -0.20f, -0.60f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, -0.80f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.20f, -0.60f, 0.0f, 1.0f, 0.0f, 1.0f,
		   -0.20f, -0.60f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.20f, -0.60f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.40f, -0.80f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.60f, -0.60f, 0.0f, 1.0f, 0.0f, 1.0f,
		   -0.20f, 0.20f, 0.75f, 0.75f, 0.75f, 1.0f,
			0.0f, 0.20f, 0.75f, 0.75f, 0.75f, 1.0f,
		   -0.20f, 0.40f, 0.75f, 0.75f, 0.75f, 1.0f,
		   -0.20f, 0.40f, 0.75f, 0.75f, 0.75f, 1.0f,
			0.0f, 0.60f, 0.75f, 0.75f, 0.75f, 1.0f,
			0.0f, 0.20f, 0.75f, 0.75f, 0.75f, 1.0f,
			0.0f, 0.60f, 0.75f, 0.75f, 0.75f, 1.0f,
			0.20f, 0.40f, 0.75f, 0.75f, 0.75f, 1.0f,
			0.0f, 0.40f, 0.75f, 0.75f, 0.75f, 1.0f,
			0.20f, 0.40f, 0.75f, 0.75f, 0.75f, 1.0f,
			0.20f, 0.20f, 0.75f, 0.75f, 0.75f, 1.0f,
			0.0f, 0.20f, 0.75f, 0.75f, 0.75f, 1.0f,
			0.0f, 0.40f, 0.75f, 0.75f, 0.75f, 1.0f,
			0.20f, 0.40f, 0.75f, 0.75f, 0.75f, 1.0f,
			0.0f, 0.20f, 0.75f, 0.75f, 0.75f, 1.0f,
			0.0f, 0.31f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.08f, 0.40f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 0.50f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 0.50f, 0.0f, 0.0f, 0.0f, 1.0f,
			-0.07f, 0.39f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 0.31f, 0.0f, 0.0f, 0.0f, 1.0f
};

const std::vector<float> PICKUP_VERTS = {
		0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,-0.20f, -0.40f, 1.0f, 0.0f, 1.0f, 1.0f,-0.40f, -0.20f, 1.0f, 0.0f, 1.0f, 1.0f,0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,-0.40f, 0.20f, 1.0f, 0.0f, 1.0f, 1.0f,-0.20f, 0.40f, 1.0f, 0.0f, 1.0f, 1.0f,0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,0.20f, 0.40f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.40f, 0.20f, 1.0f, 0.0f, 1.0f, 1.0f,0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,0.40f, -0.20f, 1.0f, 0.0f, 1.0f, 1.0f,0.20f, -0.40f, 1.0f, 0.0f, 1.0f, 1.0f,0.20f, -0.40f, 0.50f, 0.50f, 0.50f, 1.0f,-0.20f, -0.40f, 0.50f, 0.50f, 0.50f, 1.0f,0.0f, 0.0f, 0.50f, 0.50f, 0.50f, 1.0f,0.40f, -0.20f, 0.50f, 0.50f, 0.50f, 1.0f,
		0.0f, 0.0f, 0.50f, 0.50f, 0.50f, 1.0f,0.40f, 0.20f, 0.50f, 0.50f, 0.50f, 1.0f,0.20f, 0.40f, 0.50f, 0.50f, 0.50f, 1.0f,-0.20f, 0.40f, 0.50f, 0.50f, 0.50f, 1.0f,0.0f, 0.0f, 0.50f, 0.50f, 0.50f, 1.0f,-0.40f, 0.20f, 0.50f, 0.50f, 0.50f, 1.0f,0.0f, 0.0f, 0.50f, 0.50f, 0.50f, 1.0f,-0.40f, -0.20f, 0.50f, 0.50f, 0.50f, 1.0f,
		0.40f, -0.20f, 1.0f, 1.0f, 0.0f, 1.0f,0.60f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,0.40f, 0.20f, 1.0f, 1.0f, 0.0f, 1.0f,-0.40f, 0.20f, 1.0f, 1.0f, 0.0f, 1.0f,-0.60f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,-0.40f, -0.20f, 1.0f, 1.0f, 0.0f, 1.0f

};

const std::vector<float> BULLET_VERTS = {

	0.0f, -0.20f, 0.47f, 1.0f, 0.11f, 1.0f,0.20f, 0.0f, 0.47f, 1.0f, 0.11f, 1.0f,0.0f, 0.0f, 0.47f, 1.0f, 0.11f, 1.0f,0.0f, 0.0f, 0.47f, 1.0f, 0.11f, 1.0f,0.20f, 0.0f, 0.47f, 1.0f, 0.11f, 1.0f,0.0f, 0.20f, 0.47f, 1.0f, 0.11f, 1.0f,0.0f, 0.20f, 0.47f, 1.0f, 0.11f, 1.0f,-0.20f, 0.0f, 0.47f, 1.0f, 0.11f, 1.0f,
	0.0f, 0.0f, 0.47f, 1.0f, 0.11f, 1.0f,0.0f, 0.0f, 0.47f, 1.0f, 0.11f, 1.0f,0.0f, -0.20f, 0.47f, 1.0f, 0.11f, 1.0f,-0.20f, 0.0f, 0.47f, 1.0f, 0.11f, 1.0f

};

const std::vector<float> ENEMY2_VERTS = {

	0.0f, 0.40f, 0.50f, 0.50f, 0.50f, 1.0f,0.20f, 0.40f, 0.50f, 0.50f, 0.50f, 1.0f,0.0f, 0.20f, 0.50f, 0.50f, 0.50f, 1.0f,0.0f, 0.20f, 0.50f, 0.50f, 0.50f, 1.0f,0.20f, 0.20f, 0.50f, 0.50f, 0.50f, 1.0f,0.20f, 0.40f, 0.50f, 0.50f, 0.50f, 1.0f,0.20f, 0.40f, 0.50f, 0.50f, 0.50f, 1.0f,0.40f, 0.20f, 0.50f, 0.50f, 0.50f, 1.0f,
	0.20f, 0.20f, 0.50f, 0.50f, 0.50f, 1.0f,0.0f, 0.40f, 0.50f, 0.50f, 0.50f, 1.0f,-0.20f, 0.40f, 0.50f, 0.50f, 0.50f, 1.0f,-0.20f, 0.20f, 0.50f, 0.50f, 0.50f, 1.0f,0.0f, 0.40f, 0.50f, 0.50f, 0.50f, 1.0f,0.0f, 0.20f, 0.50f, 0.50f, 0.50f, 1.0f,-0.20f, 0.20f, 0.50f, 0.50f, 0.50f, 1.0f,-0.20f, 0.40f, 0.50f, 0.50f, 0.50f, 1.0f,
	-0.40f, 0.20f, 0.50f, 0.50f, 0.50f, 1.0f,-0.20f, 0.20f, 0.50f, 0.50f, 0.50f, 1.0f,-0.40f, 0.20f, 0.50f, 0.50f, 0.50f, 1.0f,-0.40f, -0.20f, 0.50f, 0.50f, 0.50f, 1.0f,0.40f, -0.20f, 0.50f, 0.50f, 0.50f, 1.0f,0.40f, -0.20f, 0.50f, 0.50f, 0.50f, 1.0f,0.40f, 0.20f, 0.50f, 0.50f, 0.50f, 1.0f,-0.40f, 0.20f, 0.50f, 0.50f, 0.50f, 1.0f,
	-0.40f, -0.20f, 0.50f, 0.50f, 0.50f, 1.0f,-0.20f, -0.40f, 0.50f, 0.50f, 0.50f, 1.0f,0.0f, -0.20f, 0.50f, 0.50f, 0.50f, 1.0f,0.0f, -0.20f, 0.50f, 0.50f, 0.50f, 1.0f,0.20f, -0.40f, 0.50f, 0.50f, 0.50f, 1.0f,0.40f, -0.20f, 0.50f, 0.50f, 0.50f, 1.0f,0.12f, 0.13f, 1.0f, 1.0f, 1.0f, 1.0f,0.20f, 0.20f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.12f, 0.28f, 1.0f, 1.0f, 1.0f, 1.0f,0.0f, 0.20f, 1.0f, 1.0f, 1.0f, 1.0f,0.12f, 0.13f, 1.0f, 1.0f, 1.0f, 1.0f,0.12f, 0.28f, 1.0f, 1.0f, 1.0f, 1.0f,0.0f, 0.20f, 1.0f, 1.0f, 1.0f, 1.0f,-0.12f, 0.29f, 1.0f, 1.0f, 1.0f, 1.0f,-0.20f, 0.20f, 1.0f, 1.0f, 1.0f, 1.0f,-0.20f, 0.20f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.10f, 0.14f, 1.0f, 1.0f, 1.0f, 1.0f,0.0f, 0.20f, 1.0f, 1.0f, 1.0f, 1.0f,-0.16f, -0.04f, 1.0f, 0.0f, 0.0f, 1.0f,0.14f, -0.04f, 1.0f, 0.0f, 0.0f, 1.0f,-0.01f, -0.13f, 1.0f, 0.0f, 0.0f, 1.0f
};

const float MIN_RANGE = 0.0f;
const float MAX_RANGE = 100.0f;
const float RESULT_RANGE = 1.0f;


