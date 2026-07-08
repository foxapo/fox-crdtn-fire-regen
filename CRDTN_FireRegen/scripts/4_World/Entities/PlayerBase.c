modded class PlayerBase
{
    protected bool _campfireStat = false;

    // ** CAMPFIRE ** // 

    void SetCampfireStat(bool state)
    {
        _campfireStat = state;
    }

    bool GetCampfireStat()
    {
        return _campfireStat;
    }
}