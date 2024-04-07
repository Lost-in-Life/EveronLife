class EL_CharacterLicence
{
	protected string m_licenceName;
	
	string GetLicence()
	{
		return m_licenceName;
	}
	
	static EL_CharacterLicence Create(string licenceName)
	{
		EL_CharacterLicence licence();
		licence.m_licenceName = licenceName;
		return licence;
	}
	
	
}