class ActionCarHorn : ActionInteractBase
{
	void ActionCarHorn()
	{
		// TODO: Figure out how to use this action cmd, for some reason the player gets stuck in the horn animation (it's a loop): DayZPlayerConstants.CMD_ACTIONMOD_TOOTHORN
		m_CommandUID		= DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask		= DayZPlayerConstants.STANCEMASK_ALL;
		m_LockTargetOnUse	= false;
		m_Text				= "Press Horn";
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem		= new CCINone;
		m_ConditionTarget	= new CCTNone;
	}

	override typename GetInputType()
	{
		return CarHornActionInput;
	}

	override bool HasTarget()
	{
		return false;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		HumanCommandVehicle vehCommand = player.GetCommand_Vehicle();

		if (vehCommand)
		{
			Transport trans = vehCommand.GetTransport();
			if (trans)
			{
				CarScript car;
				if (Class.CastTo(car, trans))
				{
					if (car.CrewMemberIndex(player) == DayZPlayerConstants.VEHICLESEAT_DRIVER)
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	override void OnExecuteServer(ActionData action_data)
	{
		HumanCommandVehicle vehCommand = action_data.m_Player.GetCommand_Vehicle();
		if (vehCommand)
		{
			Transport trans = vehCommand.GetTransport();
			if (trans)
			{
				CarScript car;
				if (Class.CastTo(car, trans))
				{
					car.ServerPlayHornSound();
				}
			}
		}
	}

	override bool CanBeUsedInVehicle()
	{
		return true;
	}
};