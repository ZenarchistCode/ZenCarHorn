modded class MissionGameplay extends MissionBase
{
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);

		/*
		// Get player
		autoptr PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		// Get input controller
		autoptr Input zenInput = Input.Cast(GetGame().GetInput());

		if (!player || !zenInput)
			return;

		// If a menu is open stop here
		if (GetGame().GetUIManager().GetMenu() != null || GetGame().GetUIManager().IsCursorVisible())
		{
			return;
		}

		if (player.m_IsVehicleSeatDriver && zenInput.LocalPress("UAZenCarHorn")) // Sends request to server to play car horn
		{
			player.PlayCarHornSound();
		}*/
	}
}