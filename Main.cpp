extern void GameStart();
extern bool PlantDataInit();
extern bool BulletDataInit();
extern bool ZombieDataInit();

int main() {
	PlantDataInit();
	BulletDataInit();
	ZombieDataInit();
	GameStart();
	return 0;
}