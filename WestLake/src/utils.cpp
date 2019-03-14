#include "utils.h"
#include "threadpool.h"

std::threadpool playerThread{ 20 };
std::threadpool actorsThread{ 20 };

utils::utils()
{

}

utils::~utils()
{
}

bool utils::Init()
{
	if (!CacheGName()) return false;
	RefreshOffset();
	return true;
}

void utils::RefreshOffset()
{
	g_UWorld = dpt.de_world(UWORLD);
	printf("%IX\t%s\r\n", g_UWorld, "World");
	printf("%IX\t%s\r\n", g_UWorld, GetGNameById(g_UGname, DECID(READINT(g_UWorld + AACTORID))).c_str());
	g_ULevel = dpt.de_level(LEVEL);
	printf("%IX\t%s\r\n", g_ULevel, "Level");
	g_GameInstance = dpt.de_inst(GAMEINSTANCE);
	printf("%IX\t%s\r\n", g_GameInstance, "GameInst");
	g_ULocalPlayer = dpt.de_local(LOCALPLAYER);
	printf("%IX\t%s\r\n", g_ULocalPlayer, "LocalPlayer");
	g_APlayerController = dpt.de_controller(PLAYERCONTROLLER);
	printf("%IX\t%s\r\n", g_APlayerController, "PlayerController");
	g_UPlayerCameraManager = READ64(g_APlayerController + PLAYERCAMERAMANAGER);
	printf("%IX\t%s\r\n", g_UPlayerCameraManager, "PlayerCameraManager");
	g_USelf = dpt.de_prop(g_APlayerController + SELF);
	printf("%IX\t%s\r\n", g_USelf, "Self");
	g_MeshSelf = READ64(g_USelf + MESH);
	printf("%IX\t%s\r\n", g_MeshSelf, "MeshSelf");

	g_BestAimTarget = PlayerData {};

	printf("%s\r\n\r\n%s\r\n\r\n", "��ʼ���ɹ�", "Homeˢ�� F5��Ʒ F6���� F8��׼");
}

void utils::DebugOffset()
{
	
	printf("self ---------------------\r\n");
	for (int i = 0; i < 0x1000; i++)
	{
		uint64_t targ = dpt.de_prop(g_APlayerController + i);
		if (targ)
		{
			int id = DECID(READINT(targ + AACTORID));
			string r = GetGNameById(g_UGname, id);
			if (r.length() > 1 && r.length() < 30)
			{
				printf("%X\t%s\r\n", i, GetGNameById(g_UGname, id).c_str());
			}
		}
	}
	printf("cameraManager ---------------\r\n");

	for (int i = 0; i < 0x1000; i++)
	{
		uint64_t targ = READ64(g_APlayerController + i);
		if (targ)
		{
			int id = DECID(READINT(targ + AACTORID));
			string r = GetGNameById(g_UGname, id);
			if (r.length() > 1 && r.length() < 30)
			{
				printf("%X\t%s\r\n", i, GetGNameById(g_UGname, id).c_str());
			}
		}
	}

	printf("f r l --------------------\r\n");

	for (int i = 0; i < 0x2000; i++)
	{
		uint64_t targ = g_UPlayerCameraManager + i + 0x0;
		if (READFLT(targ) == -9204.73047f)
		{
			if (READFLT((targ + 0x4)) == 3348.46704f)
			{
				if (READFLT((targ + 0x8)) == 6156.79785f)
				{
					printf("%X\t%s\r\n", i, "Location");
				}
			}
		}

		if (READFLT(targ) == 90.00000f)
		{
			printf("%X\t%s\r\n", i, "Fov");
		}


		if (READFLT(targ) == 3.97983479f)
		{
			if (READFLT((targ + 0x4)) == 0.800000012f)
			{
				printf("%X\t%s\r\n", i, "Roator");
			}
		}
	}

	printf("team and charactermovement ---------------------\r\n");

	for (int i = 0; i < 0x3000; i++)
	{
		uint64_t targ = dpt.de_prop(g_USelf + i);
		if (targ)
		{
			int id = DECID(READINT(targ + AACTORID));
			string r = GetGNameById(g_UGname, id);
			if (r.length() > 1 && r.length() < 30)
			{
				printf("%X\t%s\r\n", i, GetGNameById(g_UGname, id).c_str());
			}
		}
	}
	printf("---------------------\r\n");

}

bool SortRule(PlayerData a, PlayerData b)
{
	float l = abs(a.screen.x - 960);
	float m = abs(a.screen.y - 540);
	float j = abs(b.screen.x - 960);
	float k = abs(b.screen.y - 540);
	return ((l * l + m * m) < (j * j + k * k)) && (a.distance < b.distance);
}

void utils::ActorLoop()
{

	//READSIZE(GAMEBASE, READBUF, 0x7162000);
	//void* base = &READBUF[0 + UWORLD];
	//uint64_t uworld1 = *(uint64_t *)(base);
	//uint64_t uworld2 = *(uint64_t *)(uworld1);
	//uint64_t uworld2 = 0;
	//printf("0x%p 0x%p 0x%IX \r\n", &READBUF, base, uworld1);
	//return;


	//////////////////////
	if (autobot)
	{
		dx.DrawLine(950, 540, 970, 540, GREEN);
		dx.DrawLine(960, 530, 960, 550, GREEN);
	}

	if (itemgoods)
	{
		dx.DrawString(false, 5, 50, RED, "��Ʒ");
	}

	if (vehicle)
	{
		dx.DrawString(false, 45, 50, RED, "����");
	}

	uint64_t aactor_ptr = dpt.de_actor(ACTORS);
	int entitycount = READINT(aactor_ptr + 0x8);
	dx.DrawString(false, 5, 20, RED, "count = %d", entitycount);
	//dx.DrawString(false, 5, 50, RED, "speed = %f", GetBulletSpeed(g_USelf));
	if (entitycount < 1) return;
	uint64_t actors = READ64(aactor_ptr);
	if (!actors) return;

	aimList.clear();
	//actorCount = 0;
	for (int i = 0; i < entitycount; i++)
	{
		FCameraCache = READT(FCameraCacheEntry, g_UPlayerCameraManager + CAMERACACHE, sizeof(FCameraCacheEntry));
		uint64_t actor = READ64(actors + (i * 0x8));
		if (!actor || actor == g_USelf) continue;
		int id = DECID(READINT(actor + AACTORID));
		//printf("%s \r\n", GetGNameById(g_UGname, id).c_str());
		if (id > 0 && id < CachedNames.size())
		{

			if (isPlayer(id) || isVehicle(id) || isItems(id) || isLoot(id) || isAircaft(id))
			{
				if (esp && isPlayer(id))
				{
					//actorCount++;
					Vector3 localLocation = FCameraCache.POV.Location;

					//for (int i = 0; i < 0x1000; i++)
					//{
					//	uint64_t targ = dpt.de_prop(actor + i);
					//	if (targ)
					//	{
					//		int id = DECID(READINT(targ + AACTORID));
					//		string r = GetGNameById(g_UGname, id);
					//		if (r.length() > 1 && r.length() < 30)
					//		{
					//			printf("%X\t%s\r\n", i, GetGNameById(g_UGname, id).c_str());
					//		}
					//	}
					//}

					//for (int i = 0; i < 0x3000; i++)
					//{
					//	uint64_t targ = dpt.de_prop(actor + i);
					//	if (targ)
					//	{
					//		int id = DECID(READINT(targ + AACTORID));
					//		string r = GetGNameById(g_UGname, id);
					//		if (r.length() > 1 && r.length() < 30)
					//		{
					//			printf("%X\t%s\r\n", i, GetGNameById(g_UGname, id).c_str());
					//		}
					//	}
					//}

					uint64_t root = dpt.de_prop(actor + ROOTCOMPONET);
					Vector3 actor_location = READT(Vector3, root + RELATIVELOCATION, sizeof(Vector3));
					Vector3 actorScreen = WorldToScreen(actor_location, FCameraCache);
					float distance = (actor_location - localLocation).Length() / 100.0f;

					if (dpt.de_prop(actor + TEAM)) continue;
					float health = READFLT(actor + HEALTH);
					float groggyHealth = READFLT(actor + GROGGYHEALTH);

					if (abs(actor_location.x - localLocation.x) < 25001 && abs(actor_location.y - localLocation.y) < 25001 && (health > 0 || groggyHealth > 0))
					{
						int radarx = (actor_location.x - localLocation.x) / 10000 * 64 + (1920 - 167);
						int radary = (actor_location.y - localLocation.y) / 10000 * 64 + (1080 - 160);
						dx.DrawString(true, radarx, radary, RED, "��");
					}


					if (inScreen(actorScreen))
					{
						DWORD_PTR mesh = READ64(actor + MESH);
						bool canVisual = READFLT(mesh + LASTRENDERTIME) == READFLT(g_MeshSelf + LASTRENDERTIME);
						int headId = 15;
						Vector3 headLocation = GetBoneWithRotation(mesh, headId);
						actorScreen = WorldToScreen(headLocation, FCameraCache);

						if (autobot && health > 0.0f && canVisual && distance < 800 && abs(actorScreen.x - 960) < AIMBOTCIRCLESIZE && abs(actorScreen.y - 540) < AIMBOTCIRCLESIZE)
						{
							PlayerData _pdata;
							_pdata.actor = actor;
							_pdata.root = root;
							_pdata.mesh = mesh;
							_pdata.isVisual = canVisual;
							_pdata.screen = actorScreen;
							_pdata.distance = distance;
							_pdata.health = health;
							_pdata.groggyHealth = groggyHealth;
							aimList.push_back(_pdata);
						}


						//dx.DrawString(true, actorScreen.x, actorScreen.y - 25, RED, "%IX", actor);

						if (health > 0.0f) {
							if (g_BestAimTarget.actor == actor)
							{
								dx.DrawString(true, actorScreen.x, actorScreen.y - 20.0f + (distance / 50) * 1.0f, RED, "[%.0f] [%.0f]", distance, health);
							}
							else
							{
								dx.DrawString(true, actorScreen.x, actorScreen.y - 20.0f + (distance / 50) * 1.0f, canVisual ? VISUAL : UNVISUAL, "[%.0f]", distance);
							}

							if (skeltch && distance < 250)
							{
								DrawSkeleton(mesh, canVisual);
							}
						}
						else
						{
							if (groggyHealth > 0.0f) {
								dx.DrawString(true, actorScreen.x, actorScreen.y, WHITE, "��[%0.0f][%0.0f]", distance, groggyHealth);
							}
						}

						/*---------------------------------------------------------------------------------------------------------*/
						//DWORD_PTR WeaponProcessor = READ64(actor + WEAPONPROCESSOR);
						//DWORD_PTR EquippedWeapons = READ64(WeaponProcessor + EQUIPPEDWEAPONS);
						//BYTE CurrentWeaponIndex = READBYTE(WeaponProcessor + EQUIPPEDWEAPONS + 0x20 + 0x1);
						//if (CurrentWeaponIndex >= 0 && CurrentWeaponIndex < 3)
						//{
						//	DWORD_PTR pWeapon = READ64(EquippedWeapons + CurrentWeaponIndex * 8);
						//	if (pWeapon)
						//	{
						//		DWORD_PTR pData = READ64(pWeapon + WEAPONTRAJECTORYDATA); // WEAPONTRAJECTORYDATA
						//		
						//		float TrajectoryGravityZ = READFLT(pWeapon + TARJECTORYGRAVITYZ); //TrajectoryGravityZ
						//		float SimulationSubstepTime = READFLT(pData + TRAJECTORYCONFIG + SIMULATIONSUBSTEPTIME); // SimulationSubstepTime
						//		float VDragCoefficient = READFLT(pData + TRAJECTORYCONFIG + 0x20); // VDragCoefficient
						//		float BulletSpeed = READFLT(pData + TRAJECTORYCONFIG);             // BulletSpeed
						//		float BulletFlyDistancePerTick = SimulationSubstepTime * BulletSpeed;
						//		float flyDist = 0.0f;
						//		float tmp = 0.0f;

						//		int tick = 0;
						//		for (int i = 1; i <= 500; i++)
						//		{

						//			flyDist = BulletFlyDistancePerTick * (tick = i);

						//			tmp = TrajectoryGravityZ * SimulationSubstepTime * 100.0f * VDragCoefficient  * (i - 1) * SimulationSubstepTime;

						//			if (flyDist > distance) break;
						//		}
						//		flyDist -= BulletFlyDistancePerTick;

						//		dx.DrawString(true, actorScreen.x, actorScreen.y + 10, RED, "%f %d %f %f %f %f", flyDist, tick, tmp, TrajectoryGravityZ, SimulationSubstepTime, VDragCoefficient);

						//	}
						//}
						/*---------------------------------------------------------------------------------------------------------*/

					}
				}

				if (vehicle && isVehicle(id))
				{
					Vector3 localLocation = FCameraCache.POV.Location;
					uint64_t root = dpt.de_prop(actor + ROOTCOMPONET);
					Vector3 actor_location = READT(Vector3, root + RELATIVELOCATION, sizeof(Vector3));
					Vector3 actorScreen = WorldToScreen(actor_location, FCameraCache);
					float distance = (actor_location - localLocation).Length() / 100.0f;
					if (inScreen(actorScreen))
					{
						dx.DrawString(true, actorScreen.x, actorScreen.y, getColor(CachedNames[id]), "%s [%0.0f]", CachedNames[id].c_str(), distance);
					}


				}

				if (itemgoods &&  isItems(id))
				{

					if (GetAsyncKeyState(VK_F7) & 1)
					{
						printf("DroppedItemGroupArray \r\n");
						for (int i = 0; i < 0x1000; i++)
						{
							uint64_t targ = READ64(READ64(actor + i));
							if (targ)
							{
								int id = DECID(READINT(targ + AACTORID));
								string r = GetGNameById(g_UGname, id);
								if (r.length() > 1 && r.length() < 30)
								{
									printf("%X\t%s\r\n", i, GetGNameById(g_UGname, id).c_str());
								}
							}
						}
					}

					Vector3 localLocation = FCameraCache.POV.Location;
					uint64_t root = dpt.de_prop(actor + ROOTCOMPONET);
					Vector3 actor_location = READT(Vector3, root + RELATIVELOCATION, sizeof(Vector3));

					uint64_t DroppedItemGroupArray = READ64(actor + DROPPEDITEMARRAY);
					int count = READINT(actor + DROPPEDITEMARRAY + 0x8);
					if (!count) continue;
					int z = 0;
					for (int j = 0; j < count; j++)
					{
						uint64_t DroppedItemGroup = READ64(DroppedItemGroupArray + j * 0x10);
						uint64_t UItem = READ64(DroppedItemGroup + UITEM);
						int uid = DECID(READINT(UItem + AACTORID));

						if (uid < CachedNames.size() && strlen(CachedNames[uid].c_str()) < 7)
						{
							Vector3 goods_location = READT(Vector3, DroppedItemGroup + RELATIVELOCATION, sizeof(Vector3));
							Vector3 goods_screen = WorldToScreen(goods_location, FCameraCache);
							float d = (goods_location - localLocation).Length() / 100.0f;
							if (inScreen(goods_screen))
							{
								goods_screen.y -= (z++) * 8;
								dx.DrawString(true, goods_screen.x, goods_screen.y, getColor(CachedNames[uid]), "%s [%0.0f]", CachedNames[uid].c_str(), d);
							}
						}
					}

				}

				if (itemgoods &&  isLoot(id))
				{
					Vector3 localLocation = FCameraCache.POV.Location;
					uint64_t root = dpt.de_prop(actor + ROOTCOMPONET);
					Vector3 actor_location = READT(Vector3, root + RELATIVELOCATION, sizeof(Vector3));
					Vector3 actorScreen = WorldToScreen(actor_location, FCameraCache);
					float distance = (actor_location - localLocation).Length() / 100.0f;

					if (inScreen(actorScreen))
					{
						if (distance < 250.0f)
						{
							DWORD_PTR Items = READ64(actor + ITEMPACKAGE);
							int Count = READINT(actor + ITEMPACKAGE + 0x8);
							if (Count < 1 || Count > 64) continue;
							for (int j = 0; j < Count; j++)
							{
								DWORD_PTR Item = READ64(Items + j * 0x8);
								int uid = DECID(READINT(Item + AACTORID));
								if (uid < CachedNames.size() && strlen(CachedNames[uid].c_str()) < 7)
								{
									actorScreen.y += 14;

									dx.DrawString(true, actorScreen.x, actorScreen.y, getColor(CachedNames[uid]), "%s [%0.0f]", CachedNames[uid].c_str(), distance);
								}
							}
						}
					}
				}

				if (itemgoods &&  isAircaft(id))
				{
					Vector3 localLocation = FCameraCache.POV.Location;
					uint64_t root = dpt.de_prop(actor + ROOTCOMPONET);
					Vector3 actor_location = READT(Vector3, root + RELATIVELOCATION, sizeof(Vector3));
					Vector3 actorScreen = WorldToScreen(actor_location, FCameraCache);
					float distance = (actor_location - localLocation).Length() / 100.0f;

					if (inScreen(actorScreen))
					{
						dx.DrawString(true, actorScreen.x, actorScreen.y, BLUE, "%s [%0.0f]", "��Ͷ", distance);
					}
				}
			}

		}
	}
	aimList.sort(SortRule);

	//dx.DrawString(true, 10, 300, RED, "%d", actorCount);

	if (((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0 || (GetAsyncKeyState(VK_LSHIFT) & 0x8000) != 0) && g_BestAimTarget.actor != 0)
	{

	}
	else {
		if (aimList.size() > 0)
		{
			if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) == 0 && (GetAsyncKeyState(VK_LSHIFT) & 0x8000) == 0)
			{
				g_BestAimTarget = *aimList.begin();
			}
			else if (g_BestAimTarget.actor == 0)
			{
				g_BestAimTarget = *aimList.begin();
			}
		}
		else {
			g_BestAimTarget = PlayerData{ 0, 0, 0, false, Vector3(0,0,0) , 0.f,0.f,0.f };
		}
	}

}

void utils::EspPlayers(list<uint64_t> players)
{
}

void utils::EspItems(list<uint64_t> items)
{

}

void utils::EspVehicles(list<uint64_t> vehicles)
{

}

void utils::Fire()
{
	if (!g_BestAimTarget.actor)
	{
		return;
	}

	if (!g_BestAimTarget.isVisual)
	{
		g_BestAimTarget = PlayerData{};
		return;
	}
	FCameraCache = READT(FCameraCacheEntry, g_UPlayerCameraManager + CAMERACACHE, sizeof(FCameraCacheEntry));
	int headId = ((GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0) ? 4 : 15;	
	Vector3 headLocation = GetBoneWithRotation(g_BestAimTarget.mesh, headId);
	
	uint64_t VehicleRiderComponent = READ64(g_BestAimTarget.actor + VEHICLERIDERCOMPONENT);
	int SeatIndex = READINT(VehicleRiderComponent + SEATINDEX);
	Vector3 Velocity;
	
	if (SeatIndex == -1)
	{
		Velocity = READT(Vector3, g_BestAimTarget.root + COMPONENTVELOCITY, sizeof(Vector3));
	}
	else {
		Velocity = READT(Vector3, READ64(VehicleRiderComponent + LASTVEHICLEPAWN) + REPLICATEDMOVEMENT, sizeof(Vector3));
	}
			
	//float flTime = GetBulletFlyTime(g_USelf, g_BestAimTarget.distance);
	float speed = GetBulletSpeed(g_USelf);
	float flTime = g_BestAimTarget.distance / speed;


	Vector3 PredictedPos;
	PredictedPos.x = headLocation.x + (Velocity.x * flTime);
	PredictedPos.y = headLocation.y + (Velocity.y * flTime);
	float cz = 0.00f;
	if (g_BestAimTarget.distance <= 100.0f)
	{
		cz -=  ((100 - g_BestAimTarget.distance) / 10);
		PredictedPos.z = headLocation.z + (Velocity.z * flTime) + cz;
	}
	if (g_BestAimTarget.distance > 100.0f)
	{
		// 9.80665f
		//float t = GetBulletFlyTime(g_USelf, g_BestAimTarget.distance - 100.000000f);
		float t = (g_BestAimTarget.distance - 100.000000f) / speed;
		cz = 0.500000f * 9.80665f * t * t * 100;
		PredictedPos.z = headLocation.z + (Velocity.z * t) + cz;
	}

	DWORD_PTR AnimScriptInst = READ64(g_MeshSelf + ANIMSCRIPTINSTANCE);
	FRotator ControlRotation_CP = READT(FRotator, AnimScriptInst + CONTROLROTATION_CP, sizeof(FRotator));
	FCameraCache.POV.Rotation = ControlRotation_CP;
	Vector3 aimScreen = WorldToScreen(PredictedPos, FCameraCache);

	int x = (int)(aimScreen.x - 960);
	int y = (int)(aimScreen.y - 540);
	if (abs(x) < AIMBOTCIRCLESIZE * 3  && abs(y) < AIMBOTCIRCLESIZE * 3)
	{
		mouse_event(MOUSEEVENTF_MOVE, x, y, 0, 0);
	}
	
}