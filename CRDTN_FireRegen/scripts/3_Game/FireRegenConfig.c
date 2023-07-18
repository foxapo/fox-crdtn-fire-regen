class FireRegenConfig
{
    float HealRadius                    = 3;        // Radius in meters
    float HealTreshold                  = 100;
    float BloodTreshold                 = 5000;
    float HealRatePerTick               = 0.25;     // Amount of stat add/subtract per TickIntervalActive
    float BloodRatePerTick              = 0.25;
    string HealNotificationStarted      = "";       // If blank, no notifications 
    string HealNotificationEnded        = "";
    bool IndoorOnly                     = true;     // If false, works on every fireplace object
    float TickIntervalInactive          = 10.0;
    float TickIntervalActive            = 10.0;

    static void Load(out FireRegenConfig instance)
    {
        JsonFileLoader<ref FireRegenConfig>.JsonLoadFile(CFG_FireRegensConfig, instance);
        // if the file does not exist, create it
        if (instance == null)
        {
            instance = new FireRegenConfig();
            Save(instance);
            Print(CFG_FireRegenPrefix + "Config file not found, creating new one!");
        }else{
            Print(CFG_FireRegenPrefix + "Config loaded from " + CFG_FireRegensConfig);
        }
        
        Print(CFG_FireRegenPrefix + "HealTreshold: " + instance.HealTreshold);
        Print(CFG_FireRegenPrefix + "BloodTreshold: " + instance.BloodTreshold);
        Print(CFG_FireRegenPrefix + "HealRadius: " + instance.HealRadius);
        Print(CFG_FireRegenPrefix + "HealRatePerTick: " + instance.HealRatePerTick);
        Print(CFG_FireRegenPrefix + "BloodRatePerTick: " + instance.BloodRatePerTick);
        Print(CFG_FireRegenPrefix + "HealNotificationStarted: " + instance.HealNotificationStarted);
        Print(CFG_FireRegenPrefix + "HealNotificationEnded: " + instance.HealNotificationEnded);
        Print(CFG_FireRegenPrefix + "IndoorOnly: " + instance.IndoorOnly);
        Print(CFG_FireRegenPrefix + "TickIntervalInactive: " + instance.TickIntervalInactive);
        Print(CFG_FireRegenPrefix + "TickIntervalActive: " + instance.TickIntervalActive);
    }

    static void Save(ref FireRegenConfig instance)
    {
        JsonFileLoader<ref FireRegenConfig>.JsonSaveFile(CFG_FireRegensConfig, instance);
        Print(CFG_FireRegenPrefix + "Saving config to " + CFG_FireRegensConfig);
    }
}