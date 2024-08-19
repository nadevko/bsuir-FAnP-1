{
  pkgs ? import <nixpkgs> { overlays = [ (import <bsuir-tex/nixpkgs>) ]; },
}:
pkgs.mkShell {
  name = "FAnP-1";
  packages = [
    (pkgs.texliveSmall.withPackages (_: with pkgs.texlivePackages; [ bsuir-tex ]))
    pkgs.python312Packages.pygments
    pkgs.inkscape-with-extensions
  ];
}
