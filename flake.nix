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
          shellHook = ''
            generate_protos() {
              protoc --proto_path=protos/defs --cpp_out=protos/src protos/defs/meng.proto
            }
          '';
          buildInputs = with pkgs; [
            protobuf3_21
          ];
        };
      in {
        devShells.default = shell;
      }
    );
}
