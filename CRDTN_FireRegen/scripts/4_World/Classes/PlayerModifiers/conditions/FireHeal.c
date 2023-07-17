class FireHeal : ModifierBase
{
    private    const    float   HEAL_TRESHOLD               = 100;
    private    const    float   FIREPLACE_HEAL_RADIUS       = 3;
    private             float   HEALTH_INCREMENT_PER_SEC    = 0.25;
    private             string  NOTIFICATION_STARTED        = "I feel really good at this fireplace!";
    private             string  NOTIFICATION_ENDED          = "...";
    
    void FireHeal(float increment_per_sec, string notification_started = "I feel really good at this fireplace!", string notification_ended = "...")
    {
        HEALTH_INCREMENT_PER_SEC = increment_per_sec;
        NOTIFICATION_STARTED = notification_started;
        NOTIFICATION_ENDED = notification_ended;
    }

    override void Init()
    {
        m_TrackActivatedTime = false;
        m_ID = eFireHealModifiers.MDF_CRDTN_FIRE_HEAL;
        m_TickIntervalInactive = 10;
        m_TickIntervalActive = 10;
    }

    override bool ActivateCondition(PlayerBase player)
    {
        return IsIndoorFireplaceNearby(player) && player.GetHealth("GlobalHealth", "Health") < HEAL_TRESHOLD;
    }

    override void OnActivate(PlayerBase player)
    {
        player.MessageStatus(NOTIFICATION_STARTED);
    }

    override void OnDeactivate(PlayerBase player)
    {
        player.MessageStatus(NOTIFICATION_ENDED);
    }

    override bool DeactivateCondition(PlayerBase player)
    {
        return !IsIndoorFireplaceNearby(player) || player.GetHealth("GlobalHealth", "Health") >= HEAL_TRESHOLD;
    }

    override void OnTick(PlayerBase player, float deltaT)
    {
        float currenthealth = player.GetHealth("GlobalHealth", "Health");
        player.SetHealth("GlobalHealth", "Health", (currenthealth + (HEALTH_INCREMENT_PER_SEC * deltaT)));
    }

    private bool IsIndoorFireplaceNearby(PlayerBase player)
    {
        array<Object> nearestObjects = new array<Object>;
        GetGame().GetObjectsAtPosition(player.GetPosition(), GameConstants.ENVIRO_TEMP_SOURCES_LOOKUP_RADIUS, nearestObjects, null);
        foreach(Object nearestObject : nearestObjects)
        {
            EntityAI ent = EntityAI.Cast(nearestObject);
			if (ent && ent.IsUniversalTemperatureSource() && ent != player)
			{
                if(!ent.IsFireplace())
                    continue;

                FireplaceBase fireplace = FireplaceBase.Cast(ent);
                if(!fireplace.IsFireplaceIndoor() && !fireplace.IsIndoorOven())
                {
                    continue;
                }

                if(!fireplace.IsBurning())
                {
                    continue;
                }

				if (vector.DistanceSq(player.GetPosition(), ent.GetPosition()) > FIREPLACE_HEAL_RADIUS)
                {
					continue;
                }

				return true;
			}
        }
        return false;
    }


};