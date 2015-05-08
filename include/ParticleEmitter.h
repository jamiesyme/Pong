#pragma once

#include <vector>


class ParticleEmitter {
private:
	struct Particle {
		float x;
		float y;
		float s;
		float vx;
		float vy;
		float lifeSpan;
		float lifeLeft;
	};

public:
	struct SpawnInstructions {
		float px;
		float py;
		float size;
		float speed;
		float speedVary;
		float dir;
		float dirVary;
		float lifeSpan;
		float lifeVary;
		int num;
	};

	ParticleEmitter();
	~ParticleEmitter();
	
	void Tick();
	void Draw();
	
	void Spawn(SpawnInstructions instructions);
	
private:
	std::vector<Particle> m_particles;
};
