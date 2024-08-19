{
  pkgs ? import <nixpkgs> { overlays = [ (import <bsuir-tex/nixpkgs>) ]; },
}:
with pkgs;
mkShell rec {
  name = "FAnP-1";

  vscode-settings = writeText "settings.json" (
    builtins.toJSON { "clangd.path" = "${pkgs.clang-tools}/bin/clangd"; }
  );

  packages = [
    (texliveSmall.withPackages (_: with texlivePackages; [ bsuir-tex ]))
    python312Packages.pygments
    inkscape-with-extensions
  ];

  shellHook = ''
    mkdir .vscode &>/dev/null
    cp ${vscode-settings} .vscode/settings.json
  '';
}
