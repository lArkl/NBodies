const int axis = 3;
const int N = 48;
const float G = 10;
const float limit = 50;
const float velMax = 10;
const float tol = 1e-3;

class Body{
	public:
	//Posiciones x,y,z
	float pos[axis];
	//Velocidades x,y,z
	float vel[axis];
	//Aceleraciones x,y,z
	//float acc[axis];
	//Masa
	float mass;
	Body();
	Body(int);
	Body(const Body &);
	void setBody(int);
	void setDefinedBody(int);
	void update(float *,float);
	void info();
	~Body();
};

class NBody{
	public:
	Body *bodies;
	Body *cpy;
	int bodyNum;
	float dt;
	NBody();
	NBody(float);
	NBody(float, int);
	NBody(const NBody &);
	void force();	
	void integr();
	~NBody();
};