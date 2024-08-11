{
  pkgs ? import <nixpkgs> { },
}:
with pkgs;
mkShell {
  name = "FAnP-1";
  packages = [ ];
}
