
# Map Editor

- Vector based editor that outputs tiles and maps.
- Draw platforms and shapes using vectors.
- Assign shaders
- Creates a pixel perfect version of the map.
- This is split into tiles of the required size.
- Unique tiles are found and deduplicated.
- Various block compression algorithms can be used to generate final output map data

## Vector editing

Platforms

Shape composed of 4 edges.
Each edge has pre-defined properties.

Top edge is intended for player to walk on.

Nodes can be added and moved around.

