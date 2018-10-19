#include "Nbody.h"
#include <iostream>
#include <random>
#include <omp.h>
using namespace std;

Body::Body(){}

Body::Body(int limit){
	for(int i=0; i< axis; ++i){
		pos[i] = rand()/(float)RAND_MAX *limit -limit*0.5;
		vel[i] = 0;//velMax * rand()/(float)RAND_MAX;
		//acc[i] = 0;
	}
	mass = 1;//rand()/RAND_MAX;
}

Body::Body(const Body &b){
	for(int i=0; i< axis; ++i){
		pos[i] = b.pos[i];
		vel[i] = b.vel[i];
		//acc[i] = b.acc[i];
	}
	mass = b.mass;
}

void Body::setBody(int limit){
	for(int i=0; i < axis; ++i){
		pos[i] = rand()/(float)RAND_MAX *limit -limit*0.5;
		if(i!=1) pos[i] *= 1.7; // WideScreen Ratio
		vel[i] = 0;//rand()/(float)RAND_MAX;
	}
	mass = 1;//rand()/RAND_MAX;
}

void Body::setDefinedBody(int limit){
	for(int i=0; i < axis; ++i){
		pos[i] = limit*0.5;//i!=2? limit * 0.5:0;
		vel[i] = 0;//rand()/(float)RAND_MAX;
	}
	mass = 1;//rand()/RAND_MAX;
}

void Body::update(float *acc, float dt){
	for(int i=0; i < axis; ++i){
		//this->acc[i] += acc[i]; 
		vel[i] += acc[i]*dt;
		pos[i] += vel[i]*dt;
	}
}

void Body::info(){
	printf("Vel:");
	for(int i=0;i<axis;++i){
		printf("  %.2f",vel[i]);
	}printf("\n");
}

Body::~Body(){}

NBody::NBody(){
	bodies = nullptr;
	cpy = nullptr;
}

//Testeo
NBody::NBody(float dif){
	dt = dif;
	bodyNum = 2;
	bodies = new Body[2];
	cpy = new Body[2];
	
	bodies[0].setDefinedBody(limit);
	cpy[0] = bodies[0];
	bodies[1].setDefinedBody(-limit);
	cpy[1] = bodies[1];
}

NBody::NBody(float dif, int num){
	dt = dif;
	bodyNum = num;
	bodies = new Body[num];
	cpy = new Body[num];
	
	for(int i=0; i < num; ++i){
		bodies[i].setBody(limit);
		cpy[i] = bodies[i];
	}
}

NBody::NBody(const NBody &nb){
	dt = nb.dt;
	bodyNum = nb.bodyNum;
	bodies = new Body[bodyNum];
	cpy = new Body[bodyNum];
	
	for(int i=0; i < bodyNum; ++i){
		bodies[i] = nb.bodies[i];
	}
}

void NBody::force(){
	//#pragma omp for
	for(int i=0; i < bodyNum; ++i){
		float acc[axis] = { };
		int collision = 0;
		for(int j=0; j < bodyNum; ++j){
			
			if( j == i )continue; //No se va a comparar a si mismo
			
			//float auxAcc[axis];
			//float distance = 0;
			//Compara por eje
			//printf("dif %d-%d: ", i,j);
			
			/*
			for(int k = 0; k < axis; ++k){
				float deltaPos = bodies[j].pos[k] - bodies[i].pos[k];
				int direction = deltaPos > 0 ? 1: -1;
				float deltaPos2 = deltaPos * deltaPos; // Norma
				
				float deltaA = deltaPos2 > tol ?
					G * bodies[j].mass / deltaPos2 : 0.0;
				auxAcc[k] = direction * deltaA;
				distance += deltaPos2;
				if(i==0)printf("%.4f ", deltaPos2);
			}printf("\n");
			if(distance <= tol*3){ //colision
				collision++;
				break;
			}
			else{
				for(int k=0; k< axis; ++k)
					acc[k] += auxAcc[k];
			}
			*/
			float distance2 = 0;
			float dist[axis]={};
			for(int k = 0; k < axis; ++k){
				float deltaPos = bodies[j].pos[k] - bodies[i].pos[k];
				dist[k] = abs(deltaPos) > tol ? deltaPos:0;
				distance2 += dist[k]*dist[k];
			}
			
			float div = pow(distance2,1.5);
			if(div <= tol*axis){ //colision
				collision++;
				break;
			}
			else{
				//float div = pow(distance2,1.5);
				for(int k=0; k< axis; ++k){
					float force = dist[k] != 0 ? 
						G*bodies[j].mass * dist[k] / div: 0;
					acc[k] += force;
				}
			}
		}
		if(!collision)
			cpy[i].update(acc,dt);
	}
	//Actualizamos la posicion y velocidad
	for(int i=0; i < bodyNum; ++i){
		bodies[i] = cpy[i];
	}
	//#pragma omp barrier
}

NBody::~NBody(){
	if(cpy != nullptr)
		delete[] cpy;
	if(bodies != nullptr)
		delete[] bodies;
}
