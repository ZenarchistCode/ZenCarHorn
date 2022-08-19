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
		if (!player || !player.IsAlive() || player.IsUnconscious())
			return false;

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
						// Perform action checks.
						if (car.IsVitalCarBattery() || car.IsVitalTruckBattery())
						{
							EntityAI battery = null;

							if (car.IsVitalCarBattery()) // Check for car battery.
							{
								battery = EntityAI.Cast(car.FindAttachmentBySlotName("CarBattery"));
							}
									
							if (car.IsVitalTruckBattery()) // Check for truck battery.
							{
								battery = EntityAI.Cast(car.FindAttachmentBySlotName("TruckBattery"));
							}

							if (battery && !battery.IsRuined()) // If required battery exists, we can use the horn.
							{
								return true;
							}
						}
					}
				}
			}
		}

		return false; // No battery, no horn. No horn, no ladies.
	}

	// When action is triggered on the server, we need to tell the car to sound the horn so that all players nearby can hear it.
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