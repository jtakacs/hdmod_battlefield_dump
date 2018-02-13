// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "HoMM3_headers\homm3\HoMM3_Extra.h"
#include <stdio.h>

Patcher* _P;
PatcherInstance* _PI;
static _bool_ plugin_On = 0;
static char* pluginName="HD.Plugin.TestPlugin";
static const _int32_ hookAddress=0x004627BC;
static const _int32_ returnAddress=0x004627C1;
static const _int32_ obstacleGeneratorFunction=0x00465E70;
static	int W_X=0x1AED3;
static	int W_Y=0x28F79;
static	int W_Z=0x13EA1;

void resetHexes(){
	for(int i=0; i<187; i++){
		o_BattleMgr->hex[i].ObstacleNum=-1;
		o_BattleMgr->hex[i].Flags=0;
	}
}

void resetRandomSeed(const int mapX,const int mapY){
	SetRandSeed(mapX*W_X+mapY*W_Y+W_Z);
	Rand(); //battle music ID
}

void writeLine(FILE * const file, const int terrainID, const int mapX, const int mapY){
	fprintf(file, "%2d, %3d, %3d, ",terrainID, mapX, mapY);	
	for(int i=0; i<187; i++){
		int n=o_BattleMgr->hex[i].Flags ;
		int m=o_BattleMgr->hex[i].ObstacleNum;
		if(n>1 /*|| m>-1*/){
			fprintf(file,"1");
		}else{
			fprintf(file,"0");
		}
	}
	fprintf(file,"\n");
}

void iterateBattlefields(const int ecx){
	// TODO for(terrainID in [0..18]
	// TODO get real terrain ID
	// TOOD handle special terrain
	// Bugger all this, I just created a testmap with 18 ground types in sequential order. 
	static int terrainID=-1;
	terrainID++;
	char path[100];
	sprintf(path,"C:\\tmp\\obst_%02d.csv",terrainID);
	FILE *file=fopen(path,"w");
	fprintf(file,"terrainID, mapX, mapY, obstacleMask\n");
	for(int mapX=0; mapX<144; mapX++){
		for(int mapY=0; mapY<144; mapY++){
			resetHexes();
			resetRandomSeed(mapX,mapY);
			CALL_1(char, __fastcall, obstacleGeneratorFunction, ecx);
			writeLine(file,terrainID,mapX,mapY);
		}
		fflush(file);
	}
	fclose(file);		
}

int __stdcall testHook(LoHook* h, HookContext* c)
{
	iterateBattlefields(c->ecx);
	c->return_address=returnAddress;
	return NO_EXEC_DEFAULT;
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		if ( !plugin_On )
		{
			plugin_On = 1; 
			_P = GetPatcher();
			_PI = _P->CreateInstance(pluginName);
			_PI->WriteLoHook(hookAddress, testHook);
		}
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	default:
		break;
	}
	return TRUE;
}

