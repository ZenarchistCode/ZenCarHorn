class CfgPatches
{
	class ZenCarHorn
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[] = { "DZ_Data" };
	};
};

class CfgMods
{
	class ZenCarHorn
	{
		dir="ZenCarHorn";
		picture=""; 
		action="";
		hideName=1;
		hidePicture=1;
		name="Zen Car Horn";
		credits=""; 
		author="Zenarchist";
		authorID="0";  
		version="1.0";
		extra=0;
		type="mod";
		inputs = "ZenCarHorn/data/inputs.xml";
		dependencies[] =
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = { "ZenCarHorn/scripts/4_world" };
			};
			class missionScriptModule
			{
				value = "";
				files[] = { "ZenCarHorn/scripts/5_mission" };
			};
		}
	};
};

class CfgVehicles
{
	class Zen_HornNoise
	{
		scope = 2;
		class HornNoiseCar
		{
			strength = 500;
			type = "shot";
		};
		class HornNoiseTruck
		{
			strength = 1000;
			type = "shot";
		};
	};
};

class CfgSoundSets
{
	// Car horns
	class Zen_CarHorn_SoundSet1 { soundShaders[] = { "Zen_CarHorn_SoundSet1" }; volumeFactor = 1.0; };
	class Zen_CarHorn_SoundSet2 { soundShaders[] = { "Zen_CarHorn_SoundSet2" }; volumeFactor = 1.0; };
	class Zen_CarHorn_SoundSet3 { soundShaders[] = { "Zen_CarHorn_SoundSet3" }; volumeFactor = 1.0; };
	// Truck horns
	class Zen_TruckHorn_SoundSet1 { soundShaders[] = { "Zen_TruckHorn_SoundSet1" }; volumeFactor = 1.0; };
	class Zen_TruckHorn_SoundSet2 { soundShaders[] = { "Zen_TruckHorn_SoundSet2" }; volumeFactor = 1.0; };
	class Zen_TruckHorn_SoundSet3 { soundShaders[] = { "Zen_TruckHorn_SoundSet3" }; volumeFactor = 1.0; };
};

class CfgSoundShaders
{
	// Car horns
	class Zen_CarHorn_SoundShader_Base
	{
		samples[] = {};
		frequency = 1;
		range = 420;
		volume = 1;
	};

	class Zen_CarHorn_SoundSet1 : Zen_CarHorn_SoundShader_Base { samples[] = { { "ZenCarHorn\data\sounds\horn1", 1 } }; };
	class Zen_CarHorn_SoundSet2 : Zen_CarHorn_SoundShader_Base { samples[] = { { "ZenCarHorn\data\sounds\horn2", 1 } }; };
	class Zen_CarHorn_SoundSet3 : Zen_CarHorn_SoundShader_Base { samples[] = { { "ZenCarHorn\data\sounds\horn3", 1 } }; };

	// Truck horns
	class Zen_TruckHorn_SoundShader_Base
	{
		samples[] = {};
		frequency = 1;
		range = 800;
		volume = 1;
	};

	class Zen_TruckHorn_SoundSet1 : Zen_TruckHorn_SoundShader_Base { samples[] = { { "ZenCarHorn\data\sounds\truckhorn1", 1 } }; };
	class Zen_TruckHorn_SoundSet2 : Zen_TruckHorn_SoundShader_Base { samples[] = { { "ZenCarHorn\data\sounds\truckhorn2", 1 } }; };
	class Zen_TruckHorn_SoundSet3 : Zen_TruckHorn_SoundShader_Base { samples[] = { { "ZenCarHorn\data\sounds\truckhorn3", 1 } }; };
};