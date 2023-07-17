modded class ModifiersManager
{
    override void Init()
    {
        super.Init();
        AddModifier(new FireHeal(0.25)); // Change the value here to change the rate of healing
    }
};