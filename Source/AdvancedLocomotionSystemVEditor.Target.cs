

using UnrealBuildTool;
using System.Collections.Generic;

public class AdvancedLocomotionSystemVEditorTarget : TargetRules
{
	public AdvancedLocomotionSystemVEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;

		ExtraModuleNames.AddRange( new string[] { "AdvancedLocomotionSystemV" } );
	}
}
