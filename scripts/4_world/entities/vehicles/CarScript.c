modded class CarScript
{
	string				m_NoiseName = "HornNoiseCar"; // Noise cfg name
	ref NoiseParams 	m_NoisePar = null; // Used for generating "noises" that zombies can hear
	NoiseSystem			m_NoiseSystem = null; // The game noise system
	int					m_HornSoundID	= 0; // Car horn sound effect file ID
	ref EffectSound		m_CarHornSound; // Car horn sound effect object

	// Called whenever a new car is created
	void CarScript()
	{
		RegisterNetSyncVariableInt("m_HornSoundID"); // Register horn sound ID for syncing to clients
	}

	// Called whenever variables sync server->client
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();

		if (m_HornSoundID != 0) // If vars have sync'd and the horn ID has changed, play a horn sound
		{
			if (m_CarHornSound && m_CarHornSound.IsPlaying())
			{
				m_HornSoundID = 0; // If a horn sound is already playing, stop here.
				return;
			}

			// Play a new car horn sound
			PlayHornSound(m_HornSoundID);
			m_HornSoundID = 0;
		}
	}

	// (Client-side) Play the given horn sound effect ID
	void PlayHornSound(int id)
	{
		m_CarHornSound = SEffectManager.PlaySound("Zen_CarHorn_SoundSet" + id.ToString(), GetFrontPointPosWS());
		m_CarHornSound.SetSoundAutodestroy(true);
	}

	// (Server-side) Send car horn sound ID to the car on client-side.
	void ServerPlayHornSound()
	{
		// Send a random car horn sound ID
		m_HornSoundID = Math.RandomIntInclusive(1, 3);
		SetSynchDirty();

		// After a couple of seconds, reset the horn sound ID so that the horn doesn't play when car enters new player's net bubble. TODO: Find a better way?
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.ServerResetHornSound, 2000, false);

		// Get noise system
		if (!m_NoiseSystem)
		{
			m_NoiseSystem = GetGame().GetNoiseSystem();
		}

		// Prepare zombie attractor
		if (m_NoiseSystem && !m_NoisePar)
		{
			m_NoisePar = new NoiseParams();
			m_NoisePar.LoadFromPath("CfgVehicles Zen_HornNoise " + m_NoiseName);
		}

		// If noise config has been loaded, play a "shot" sound to attract nearby zombies
		if (m_NoisePar)
		{
			if (m_NoiseSystem)
			{
				m_NoiseSystem.AddNoiseTarget(GetPosition(), 10, m_NoisePar);
			}
		}
	}

	// (Server-side) Reset the horn ID. If we don't do this, then if you logout after pressing car horn and log back in the car horn goes off (and scares the shit out of you)
	void ServerResetHornSound()
	{
		m_HornSoundID = 0;
		SetSynchDirty();
	}

	// Set car horn action
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionCarHorn);
	}
}