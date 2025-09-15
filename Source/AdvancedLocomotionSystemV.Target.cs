

using UnrealBuildTool;
using System.Collections.Generic;

public class AdvancedLocomotionSystemVTarget : TargetRules
{
	public AdvancedLocomotionSystemVTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;

		ExtraModuleNames.AddRange( new string[] { "AdvancedLocomotionSystemV" } );
		RegisterModulesCreatedByRider();
	}

	private void RegisterModulesCreatedByRider()
	{
		// ExtraModuleNames.AddRange(new string[] { "EditorValidDataCheck" });
	}
}
