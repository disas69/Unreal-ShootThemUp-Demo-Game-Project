// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

using UnrealBuildTool;

public class ShootThemUpEditorTarget : TargetRules
{
	public ShootThemUpEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange(new[] { "ShootThemUp" });
	}
}