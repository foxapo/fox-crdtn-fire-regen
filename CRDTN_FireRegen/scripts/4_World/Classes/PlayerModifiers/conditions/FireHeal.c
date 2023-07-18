class FireHeal : ModifierBase
{
    private  ref FireRegenConfig    m_FireRegenConfig       = NULL;
    private  float                  m_HealTreshold          = 100;
    private  float                  m_BloodTreshold         = 5000;
    private  float                  m_HealRadius            = 3;
    private  float                  m_HealRatePerTick       = 0.25;
    private  float                  m_BloodRatePerTick      = 0.25;
    private  string                 m_NotificationStarted   = "";
    private  string                 m_NotificationEnded     = "";
    private  bool                   m_IndoorOnly            = true;

    override void Init()
    {
        m_TrackActivatedTime = false;
        m_ID = eFireHealModifiers.MDF_CRDTN_FIRE_HEAL;
        SetConfigData();
    }

    override bool ActivateCondition(PlayerBase player)
    {
        return IsFireplaceNearby(player) && (player.GetHealth("GlobalHealth", "Health") < m_HealTreshold || player.GetHealth("GlobalHealth", "Blood") < m_BloodTreshold);
    }

    override void OnActivate(PlayerBase player)
    {
        SetConfigData();
        if (m_NotificationStarted != "")
            player.MessageAction(m_NotificationStarted);
    }

    override void OnDeactivate(PlayerBase player)
    {
        if (m_NotificationEnded != "")
            player.MessageAction(m_NotificationEnded);
    }

    override bool DeactivateCondition(PlayerBase player)
    {
        return !IsFireplaceNearby(player) || (player.GetHealth("GlobalHealth", "Health") >= m_HealTreshold && player.GetHealth("GlobalHealth", "Blood") >= m_BloodTreshold);
    }

    override void OnTick(PlayerBase player, float deltaT)
    {
        if(m_HealRatePerTick > 0)
        {
            float currenthealth = player.GetHealth("GlobalHealth", "Health");
            if(currenthealth < m_HealTreshold)
                player.SetHealth("GlobalHealth", "Health", (currenthealth + m_HealRatePerTick));
        }

        if(m_HealRatePerTick > 0)
        {
            float currentblood = player.GetHealth("GlobalHealth", "Blood");
            if(currentblood < m_BloodTreshold)
                player.SetHealth("GlobalHealth", "Blood", (currentblood + m_BloodRatePerTick));
        }
    }

    private bool IsFireplaceNearby(PlayerBase player)
    {
        array<Object> nearestObjects = new array<Object>;
        GetGame().GetObjectsAtPosition(player.GetPosition(), GameConstants.ENVIRO_TEMP_SOURCES_LOOKUP_RADIUS, nearestObjects, null);
        foreach (Object nearestObject : nearestObjects)
        {
            EntityAI ent = EntityAI.Cast(nearestObject);
            if (ent && ent.IsUniversalTemperatureSource() && ent != player)
            {
                if (!ent.IsFireplace())
                    continue;

                FireplaceBase fireplace = FireplaceBase.Cast(ent);
                if (m_IndoorOnly)
                { // ONLY INDOOR CHECK
                    if (!fireplace.IsFireplaceIndoor() && !fireplace.IsIndoorOven())
                    {
                        continue;
                    }
                }

                if (!fireplace.IsBurning())
                {
                    continue;
                }

                if (vector.DistanceSq(player.GetPosition(), ent.GetPosition()) > m_HealRadius)
                {
                    continue;
                }

                return true;
            }
        }
        return false;
    }

    private void SetConfigData()
    {
        m_FireRegenConfig = GetFireRegenPlugin().GetConfig();
        m_HealTreshold = m_FireRegenConfig.HealTreshold;
        m_BloodTreshold = m_FireRegenConfig.BloodTreshold;
        m_HealRadius = m_FireRegenConfig.HealRadius;
        m_HealRatePerTick = m_FireRegenConfig.HealRatePerTick;
        m_BloodRatePerTick = m_FireRegenConfig.BloodRatePerTick;
        m_NotificationStarted = m_FireRegenConfig.HealNotificationStarted;
        m_NotificationEnded = m_FireRegenConfig.HealNotificationEnded;
        m_IndoorOnly = m_FireRegenConfig.IndoorOnly;
        m_TickIntervalInactive = m_FireRegenConfig.TickIntervalInactive;
        m_TickIntervalActive = m_FireRegenConfig.TickIntervalActive;
    }
};