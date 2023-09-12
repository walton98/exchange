{
  description = "Exchange project.";

  inputs.nixpkgs.url = "github:nixos/nixpkgs";
  inputs.flake-utils.url = "github:numtide/flake-utils";


  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };

        shell = pkgs.mkShell rec {
          name = "exchange";
          buildInputs = with pkgs; [
            protobuf
          ];
        };
      in {
        devShells.default = shell;
      }
    );
}
