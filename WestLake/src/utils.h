#pragma once
#ifndef UTIL_H
#define UTIL_H

#include "common.h"
#include <list>
#include <vector>
#include <string>
#include <fstream>

using namespace std;


class utils
{
public:
	utils();
	~utils();
	bool Init();
	void RefreshOffset();
	void DebugOffset();
	void ActorLoop();
	void EspPlayers(list<uint64_t> players);
	void EspItems(list<uint64_t> items);
	void EspVehicles(list<uint64_t> vehicles);
	void Fire();

private:
	list<PlayerData> aimList;

	list<int> upper_part = { 5, 6, 15 };
	list<int> right_arm = { 5, 115, 116, 117 };
	list<int> left_arm = { 5, 88,89,90 };
	list<int> spine = { 5, 1 };
	list<int> lower_right = { 1, 174, 175, 176 };
	list<int> lower_left = { 1, 168,169,170 };
	list<list<int>> skeleton = { upper_part, right_arm, left_arm, spine, lower_right, lower_left};

	vector<string> CachedNames;
	vector<D3DCOLOR> Colors;
	FCameraCacheEntry FCameraCache;

	inline bool isPlayer(int id)
	{
		if (id < CachedNames.size())
		{
			if (CachedNames[id] == "PlayerFemale_A" || CachedNames[id] == "PlayerFemale_A_C" || CachedNames[id] == "PlayerMale_A" || CachedNames[id] == "PlayerMale_A_C")
			{
				return true;
			}
		}

		return false;
	}

	inline bool isVehicle(int id)
	{
		if (id < CachedNames.size())
		{
			if (CachedNames[id] == "吉普" || CachedNames[id] == "轿车" || CachedNames[id] == "摩托" || CachedNames[id] == "三轮" || CachedNames[id] == "四驱" || CachedNames[id] == "游艇" || CachedNames[id] == "皮卡" || CachedNames[id] == "公交" || CachedNames[id] == "雪橇") {
				return true;
			}
		}
		return false;
	}

	inline bool isItems(int id)
	{
		if (id < CachedNames.size())
		{
			if (CachedNames[id] == "DroppedItemInteractionComponent" || CachedNames[id] == "DroppedItemGroup" || CachedNames[id] == "DroppedItem")
			{
				return true;
			}
		}
		return false;
	}

	inline bool isAircaft(int id)
	{
		if (id < CachedNames.size())
		{
			if (CachedNames[id] == "Carapackage_RedBox_C")
			{
				return true;
			}
		}
		return false;
	}

	inline bool isLoot(int id)
	{
		if (id < CachedNames.size())
		{
			if (CachedNames[id] == "DeathDropItemPackage_C")
			{
				return true;
			}
		}
		return false;
	}

	inline bool inScreen(Vector3 v)
	{
		if (v.x > 0 && v.x < SCREENX && v.y >0 && v.y < SCREENY) return true;
		return false;
	}

	D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
	{
		D3DMATRIX pOut;
		pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
		pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
		pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
		pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
		pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
		pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
		pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
		pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
		pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
		pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
		pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
		pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
		pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
		pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
		pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
		pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;
		return pOut;
	}

	FTransform GetBoneIndex(DWORD_PTR mesh, int index)
	{
		DWORD_PTR boneArray = READ64(mesh + BONEARRAY);
		ULONGLONG size = sizeof(FTransform);
		return READT(FTransform, boneArray + index * size, size);
	}

	string GetGNameById(DWORD_PTR GN, uint64_t ID)
	{
		DWORD_PTR fNamePtr = READ64(GN + uint64_t(ID / GNAMECHUNKSIZE) * 8);
		DWORD_PTR fName = READ64(fNamePtr + 8 * uint64_t(ID % GNAMECHUNKSIZE));
		char resultname[256]{ NULL };
		READSIZE(fName + 0x10, resultname, sizeof(resultname));
		if (resultname != 0) {
			return string(resultname);
		}
		return "";
	}

	DWORD_PTR GetGNAMES() {
		bool found = false;
		DWORD_PTR gnames = 0;
		DWORD_PTR tmp = READ64(GAMEBASE + GNAMES);
		DWORD_PTR minval = (tmp >> 6 * 4) << 4 * 4;
		DWORD_PTR maxval = minval + 0xFFFFFF;
		for (DWORD_PTR i = minval; i < maxval; i++)
		{
			gnames = (i << 8) + GNAMESUFFIX;
			if (
				GetGNameById(gnames, 1) == string("ByteProperty")
				&& GetGNameById(gnames, 2) == string("IntProperty")
				&& GetGNameById(gnames, 3) == string("BoolProperty")
				)
			{
				found = true;
				break;
			}
		}
		printf("%IX\t%s\r\n", gnames, found ? "GNAMES 正确" : "GNAMES 错误");
		return gnames;
	}

	bool CacheGName()
	{

		if (!g_UGname)
		{
			g_UGname = GetGNAMES();
		}
		if (!g_UGname)
		{
			printf("%s\r\n", "GNAMES 错误");
			return false;
		}

		string name = "";
		ofstream log;
		if (LOGCACHE)
		{
			log.open("scan.txt");
		}

		for (int i = 0; i < 224000; i++)
		{
			name = GetGNameById(g_UGname, i);
			if (name == "Uaz_C" || name == "Uaz_A_01_C" || name == "Uaz_B_01_C" || name == "Uaz_C_01_C") {
				name = "吉普";
			}
			else if (name == "Dacia_C" || name == "Dacia_A_01_v2_C" || name == "Dacia_A_02_v2_C" || name == "Dacia_A_03_v2_C"
				|| name == "Dacia_A_04_v2_C" || name == "ABP_Dacia_01_C"
				|| name == "BP_Mirado_A_01_C" || name == "BP_Mirado_A_02_C" || name == "BP_Mirado_A_03_C" || name == "BP_Mirado_A_04_C" || name == "BP_Mirado_A_03_Esports_C"
				|| name == "BP_Mirado_Open_01_C" || name == "BP_Mirado_Open_02_C" || name == "BP_Mirado_Open_03_C" || name == "BP_Mirado_Open_04_C" || name == "BP_Mirado_Open_C")
			{
				name = "轿车";
			}
			else if (name == "ABP_Motorbike_03_C" || name == "ABP_Motorbike_04_C" || name == "BP_Motorbike_03_C" || name == "BP_Motorbike_04_C" || name == "BP_Motorbike_04_Desert_C" || name == "BP_Scooter_01_A_C" || name == "BP_Scooter_02_A_C" || name == "BP_Scooter_03_A_C" || name == "BP_Scooter_04_A_C") {
				name = "摩托";
			}
			else if (name == "ABP_Motorbike_04_Sidecar_C" || name == "BP_Motorbike_04_SideCar_C" || name == "BP_Motorbike_04_SideCar_Desert_C" || name == "ABP_Motorbike_03_Sidecart_C"
				|| name == "BP_Motorbike_03_SideCart_C" || name == "BP_Motorbike_04_Desert_C" || name == "BP_TukTukTuk_A_01_C" || name == "BP_TukTukTuk_A_02_C" || name == "BP_TukTukTuk_A_03_C") {
				name = "三轮";
			}
			else if (name == "Buggy_A_01_C" || name == "Buggy_A_02_C" || name == "Buggy_A_03_C" || name == "Buggy_A_04_C" || name == "Buggy_A_05_C" || name == "Buggy_A_06_C" || name == "Buggy_C" || name == "ABP_Buggy_02" || name == "ABP_Buggy_02_C") {
				name = "四驱";
			}
			else if (name == "AquaRail_C" || name == "AquaRail_A_01_C" || name == "Boat_PG117_C" || name == "PG117_A_01_C") {
				name = "游艇";
			}
			else if (name == "BP_M_Rony_A_01_C" || name == "BP_M_Rony_A_02_C" || name == "BP_M_Rony_A_03_C" ||
				name == "BP_PickupTruck_C" || name == "BP_PickupTruck_A_C" || name == "BP_PickupTruck_A_01_C" || name == "BP_PickupTruck_A_02_C" || name == "BP_PickupTruck_A_03_C" || name == "BP_PickupTruck_A_04_C" || name == "BP_PickupTruck_A_05_C" || name == "BP_PickupTruck_B_C" || name == "BP_PickupTruck_B_01_C" || name == "BP_PickupTruck_B_02_C" || name == "BP_PickupTruck_B_03_C" || name == "BP_PickupTruck_B_04_C" || name == "BP_PickupTruck_B_05_C")
			{
				name = "皮卡";
			}
			else if (name == "BP_Van_A_01_C" || name == "BP_Van_A_02_C" || name == "BP_Van_A_03_C" || name == "BP_MiniBus_C" || name == "ABP_Minibus_02_C")
			{
				name = "公交";
			}
			else if (name == "BP_Snowmobile_01_C" || name == "BP_Snowmobile_02_C" || name == "BP_Snowmobile_03_C" || name == "BP_Snowmobile_04_C" || name == "Dacia_A_01_v2_snow_C" || name == "Uaz_A_01_snow_C" || name == "BP_Motorbike_04_snow_C")
			{
				name = "雪橇";
			}
			else if (name == "Item_Armor_C_01_Lv3_C")
			{
				name = "三甲";
			}
			else if (name == "Item_Armor_D_01_Lv2_C")
			{

				name = "二甲";
			}
			else if (name == "Item_Head_F_01_Lv2_C" || name == "Item_Head_F_02_Lv2_C")
			{
				name = "二头";
			}
			else if (name == "Item_Head_G_01_Lv3_C")
			{

				name = "三头";
			}
			else if (name == "Item_Weapon_Grenade_C")
			{

				name = "手雷";
			}
			else if (name == "Item_Boost_AdrenalineSyringe_C")
			{

				name = "肾上腺";
			}
			else if (name == "Item_Boost_EnergyDrink_C")
			{

				name = "饮料";
			}
			else if (name == "Item_Boost_PainKiller_C")
			{

				name = "止疼";
			}
			else if (name == "Item_Heal_FirstAid_C")
			{

				name = "大药";
			}
			else if (name == "Item_Heal_MedKit_C")
			{
				name = "医疗箱";
			}
			else if (name == "Item_Weapon_Groza_C")
			{

				name = "Goza";
			}
			else if (name == "Item_Ghillie_01_C" || name == "Item_Ghillie_02_C" || name == "Item_Ghillie_03_C" || name == "Item_Ghillie_04_C")
			{
				name = "吉利服";
			}
			else if (name == "Item_Attach_Weapon_Magazine_ExtendedQuickDraw_Large_C")
			{

				name = "步快";
			}
			else if (name == "Item_Attach_Weapon_Magazine_ExtendedQuickDraw_SniperRifle_C")
			{

				name = "狙快";
			}
			else if (name == "Item_Attach_Weapon_Muzzle_Compensator_Large_C")
			{

				name = "步口";
			}
			else if (name == "Item_Attach_Weapon_Muzzle_Compensator_SniperRifle_C")
			{

				name = "狙口";
			}

			else if (name == "Item_Attach_Weapon_Muzzle_Suppressor_Large_C")
			{

				name = "步消";
			}
			else if (name == "Item_Attach_Weapon_Muzzle_Suppressor_SniperRifle_C")
			{

				name = "狙消";
			}
			else if (name == "Item_Attach_Weapon_Upper_DotSight_01_C" || name == "Item_Attach_Weapon_Upper_DotSight_Crossbow_C")
			{
				name = "红点";
			}
			else if (name == "Item_Attach_Weapon_Upper_Holosight_C")
			{

				name = "全息";
			}
			else if (name == "Item_Attach_Weapon_Upper_Aimpoint_C")
			{

				name = "2X镜";
			}
			else if (name == "Item_Attach_Weapon_Upper_Scope3x_C")
			{

				name = "3X镜";
			}
			else if (name == "Item_Attach_Weapon_Upper_ACOG_01_C")
			{

				name = "4X镜";
			}
			else if (name == "Item_Attach_Weapon_Upper_Scope6x_C")
			{

				name = "6X镜";
			}
			else if (name == "Item_Attach_Weapon_Upper_CQBSS_C")
			{

				name = "8X镜";
			}
			else if (name == "Item_Attach_Weapon_Upper_PM2_01_C")
			{

				name = "15X镜";
			}
			else if (name == "Item_Back_F_01_Lv2_C" || name == "Item_Back_F_02_Lv2_C")
			{
				name = "二包";
			}
			else if (name == "Item_Back_C_01_Lv3_C" || name == "Item_Back_C_02_Lv3_C")
			{
				name = "三包";
			}
			else if (name == "Item_Ammo_556mm_C")
			{

				name = "5.56";
			}
			else if (name == "Item_Ammo_762mm_C")
			{

				name = "7.62";
			}
			else if (name == "Item_Ammo_300Magnum_C")
			{

				name = "马格南";
			}
			else if (name == "Item_Weapon_Mk14_C")
			{

				name = "MK14";
			}
			else if (name == "Item_Weapon_FNFal_C")
			{

				name = "SLR";
			}
			else if (name == "Item_Weapon_M16A4_C")
			{

				name = "M16";
			}

			else if (name == "Item_Weapon_AK47_C")
			{

				name = "AKM";
			}
			else if (name == "Item_Weapon_AWM_C")
			{

				name = "AWM";
			}
			else if (name == "Item_Weapon_HK416_C")
			{

				name = "M4";
			}
			else if (name == "Item_Weapon_Kar98k_C")
			{

				name = "98K";
			}
			else if (name == "Item_Weapon_M24_C")
			{

				name = "M24";
			}
			else if (name == "Item_Weapon_M249_C")
			{

				name = "M249";
			}
			else if (name == "Item_Weapon_Mini14_C")
			{

				name = "Mini";
			}
			else if (name == "Item_Weapon_SCAR-L_C")
			{

				name = "SCARL";
			}
			else if (name == "Item_Weapon_SKS_C")
			{

				name = "SKS";
			}
			else if (name == "Item_Weapon_AUG_C")
			{

				name = "AUG";
			}
			else if (name == "Item_Weapon_UMP_C")
			{

				name = "UMP9";
			}
			else if (name == "Item_Weapon_UZI_C")
			{

				name = "UZI";
			}
			else if (name == "Item_Weapon_Vector_C")
			{

				name = "雷蛇";
			}
			else if (name == "Item_Weapon_Thompson_C")
			{

				name = "汤姆逊";
			}
			else if (name == "Item_Weapon_QBZ95_C")
			{

				name = "QBZ";
			}
			else if (name == "Item_Weapon_QBU88_C")
			{
				name = "QBU";
			}
			else if (name == "Item_Weapon_BerylM762_C")
			{
				name = "M762";
			}
			else if (name == "Item_Attach_Weapon_Stock_AR_Composite_C")
			{
				name = "枪托";
			}
			else if (name == "Item_Attach_Weapon_Lower_ThumbGrip_C")
			{
				name = "拇指";
			}
			else if (name == "Item_Attach_Weapon_Lower_HalfGrip_C")
			{
				name = "半截";
			}
			else if (name == "Item_Attach_Weapon_Lower_LightweightForeGrip_C")
			{
				name = "轻型";
			}
			else if (name == "Item_Attach_Weapon_Lower_AngledForeGrip_C")
			{
				name = "三角";
			}
			else if (name == "Item_Attach_Weapon_Lower_Foregrip_C")
			{
				name = "垂直";
			}
			else if (name == "Item_Attach_Weapon_Stock_SniperRifle_CheekPad_C")
			{
				name = "托腮";
			}
			else if (name == "Item_Attach_Weapon_Magazine_Extended_SniperRifle_C")
			{
				name = "狙扩";
			}
			else if (name == "Item_Attach_Weapon_Magazine_Extended_Large_C")
			{
				name = "步扩";
			}
			else if (name == "Item_Weapon_VSS_C")
			{
				name = "VSS";
			}
			else if (name == "Item_Weapon_Mk47Mutant_C")
			{
				name = "MK47";
			}
			else if (name == "Item_Weapon_G36C" || name == "Item_Weapon_G36C_C")
			{
			name = "G36";
			}
			else if (name == "Item_Weapon_vz61Skorpion_C")
			{
			name = "VZ61";
			}
			else if (name == "Item_Attach_Weapon_SideRail_DotSight_RMR_C")
			{
			name = "侧瞄";
			}
			else if (name == "Item_Weapon_FlareGun_C")
			{
			name = "信号枪";
			}
			CachedNames.push_back(name);
			if (LOGCACHE)
			{
				log << i << "\t" << name.c_str() << "\n";
			}
		}
		log.close();
		return true;
	}

	D3DCOLOR getColor(string name)
	{
		if (name == "汤姆逊" || name == "UZI" || name == "UMP9" || name == "雷蛇" || name == "AKM" || name == "M16" || name == "M762"
			|| name == "7.62" || name == "止疼" || name == "饮料" || name == "大药"
			|| name == "红点" || name == "全息" || name == "2X镜" || name == "3X镜" || name == "三角" || name == "拇指" || name == "轻型")
		{
			return LIGHTBLUE;
		}
		else if (name == "三包" || name == "M4" || name == "M249" || name == "QBZ" || name == "QBU" || name == "二包" || name == "二甲" || name == "二头"
			 || name == "SCARL" || name == "Mini" || name == "SKS" || name == "SLR" || name == "AUG"
			|| name == "Goza" || name == "吉利服" || name == "医疗箱" || name == "MK14" || name == "AWM" || name == "马格南"
			|| name == "肾上腺" || name == "MK47" || name == "VSS"
			|| name == "4X镜" || name == "6X镜" || name == "15X镜" || name == "手雷" || name == "狙口" || name == "枪托" || name == "半截" || name == "托腮" || name == "VZ61" || name == "G36")
		{
			return PURPLE;
		}
		else if (name == "5.56")
		{
			return GREEN;
		}
		else if (name == "步口" || name == "垂直" || name == "狙快"  || name == "狙扩" || name == "步扩" )
		{
			return BLUE;
		}
		else if (name == "三头" || name == "三甲" || name == "步消" || name == "步快" || name == "狙消" || name == "M24" || name == "8X镜" || name=="侧瞄" || name == "信号枪" || name == "98K")
		{
			return RED;
		}

		return WHITE;
		
	}

	inline FCameraCacheEntry GetCameraCache() {
		return READT(FCameraCacheEntry, g_UPlayerCameraManager + CAMERACACHE, sizeof(FCameraCacheEntry));
	}

	Vector3 WorldToScreen(Vector3 location, FCameraCacheEntry cameracach)
	{
		Vector3 Screenlocation = Vector3(0, 0, 0);
		auto POV = cameracach.POV;
		FRotator Rotation = POV.Rotation; // FRotator
		Vector3 vAxisX, vAxisY, vAxisZ;
		D3DMATRIX tempMatrix = Rotation.GetAxes();
		vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
		vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
		vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);
		Vector3 vDelta = location - POV.Location;
		Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

		if (vTransformed.z < 1.f)
			vTransformed.z = 1.f;

		float FovAngle = POV.FOV;
		float ScreenCenterX = SCREENX / 2.0f;
		float ScreenCenterY = SCREENY / 2.0f;

		Screenlocation.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
		Screenlocation.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
		return Screenlocation;
	}

	Vector3 GetBoneWithRotation(DWORD_PTR mesh, int id)
	{
		FTransform bone = GetBoneIndex(mesh, id);
		FTransform ComponentToWorld = READT(FTransform, mesh + COMPONENTTOWORLD, sizeof(FTransform));
		D3DMATRIX Matrix;
		Matrix = MatrixMultiplication(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());
		return Vector3(Matrix._41, Matrix._42, Matrix._43);
	}

	void DrawSkeleton(DWORD_PTR mesh, bool visual)
	{
		//1 f 2 M 0 FALSE
		// neck 5   head 6 
		FCameraCacheEntry fce = GetCameraCache();
		Vector3 neckpos = GetBoneWithRotation(mesh, 5);
		Vector3 pelvispos = GetBoneWithRotation(mesh, 1);
		Vector3 previous(0, 0, 0);
		Vector3 current, p1, c1;
		for (auto a : skeleton)
		{
			previous = Vector3(0, 0, 0);
			for (int bone : a)
			{
				current = bone == 5 ? neckpos : (bone == 1 ? pelvispos : GetBoneWithRotation(mesh, bone));
				if (previous.x == 0.f || previous.y == 0.f)
				{
					previous = current;
					continue;
				}
				p1 = WorldToScreen(previous, fce);
				c1 = WorldToScreen(current, fce);
				if (p1.Distance(c1) > 1000.f)
				{
					previous = current;
					continue;
				}
				dx.DrawLine(p1.x, p1.y, c1.x, c1.y, visual ? VISUAL : UNVISUAL);
				previous = current;
			}
		}
	}

	float GetBulletFlyTime(uint64_t targetActor, float distance)
	{
		DWORD_PTR WeaponProcessor = READ64(targetActor + WEAPONPROCESSOR);
		DWORD_PTR EquippedWeapons = READ64(WeaponProcessor + EQUIPPEDWEAPONS);
		BYTE CurrentWeaponIndex = READBYTE(WeaponProcessor + EQUIPPEDWEAPONS + 0x20 + 0x1);
		if (CurrentWeaponIndex >= 0 && CurrentWeaponIndex < 3) {
			DWORD_PTR pWeapon = READ64(EquippedWeapons + CurrentWeaponIndex * 8);
			if (pWeapon)
			{
				DWORD_PTR pData = READ64(pWeapon + WEAPONTRAJECTORYDATA);
				//float speed = READFLT(pData + TRAJECTORYCONFIG);
				//float  drag = READFLT(pData + TRAJECTORYCONFIG + VDRAGCOEFFICIENT);
				//return speed * drag;

				float TrajectoryGravityZ = READFLT(pWeapon + TRAJECTORYGRAVITYZ); //TrajectoryGravityZ
				float SimulationSubstepTime = READFLT(pData + TRAJECTORYCONFIG + SIMULATIONSUBSTEPTIME); // SimulationSubstepTime
				float drag = READFLT(pData + TRAJECTORYCONFIG + VDRAGCOEFFICIENT); // VDragCoefficient
				float BulletSpeed = READFLT(pData + TRAJECTORYCONFIG); // BulletSpeed

				float BulletFlyDistancePerTick = SimulationSubstepTime * BulletSpeed;
				float flyDist = 0.0f;
				float tmp = 0.0f;

				int tick = 0;
				for (int i = 1; i <= 500; i++)
				{

					flyDist = BulletFlyDistancePerTick * (tick = i);

					tmp = TrajectoryGravityZ * SimulationSubstepTime * 100.0f * drag  * (i - 1) * SimulationSubstepTime;

					if (flyDist > distance) break;
				}
				flyDist -= BulletFlyDistancePerTick;

				return (tick - 1) * SimulationSubstepTime;

			}
		}
		return 0.0f;
	}

	float GetBulletSpeed(uint64_t targetActor)
	{
		DWORD_PTR WeaponProcessor = READ64(targetActor + WEAPONPROCESSOR);
		DWORD_PTR EquippedWeapons = READ64(WeaponProcessor + EQUIPPEDWEAPONS);
		BYTE CurrentWeaponIndex = READBYTE(WeaponProcessor + EQUIPPEDWEAPONS + 0x20 + 0x1);
		if (CurrentWeaponIndex >= 0 && CurrentWeaponIndex < 3)
		{
			DWORD_PTR pWeapon = READ64(EquippedWeapons + CurrentWeaponIndex * 8);
			if (pWeapon)
			{
				DWORD_PTR pData = READ64(pWeapon + WEAPONTRAJECTORYDATA);
				float BulletSpeed = READFLT(pData + TRAJECTORYCONFIG); // BulletSpeed
				float drag = READFLT(pData + TRAJECTORYCONFIG + VDRAGCOEFFICIENT); // VDragCoefficient
				return BulletSpeed * drag;
			}
		}
		return 800.0f;
	}

};

#endif // !UTIL_H