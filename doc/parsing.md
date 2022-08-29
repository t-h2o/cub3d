# Parsing

## File.cub

The basic file has to have a map

```cub
  111111
 1100101
1010011
1100N1
111111
```

The element as texture'path, ceiling's color and floor's color are optional

```cub
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
F 220,100,
C 225,30,
```

## Process

1. Set a defautl value for each optional element
2. Read `file.cub`
   * Set the map
   * Set optional values if there is define in the file
   * Report any error

## Difficulty

### Check map

It's a valid map

```cub
  111111
 1100101
1010011
1100N1
111111
```

There is a `0` in the outside of the map

```cub
  111111
 110010 
1010011
1100N1
111111
```

There is a empty line in the map

```cub
  111111
 1100101

1010011
1100N1
111111
```

### Ignore blank char

```cub
     \n
\t\t\n
  111111
 1100101
1010011
1100N1
111111
   \t\n
```

### Bad information

```cub
AA ./path_to_the_texture
```

## Speudo-code

```c
char	*line;
char	**split;

while (1) {
	line = get_next_line(fd);

	// End of file
	if (line == 0)
		break ;

	// Split the file from blank char
	split = ft_blank_split(line);

	if (split == 0)
	{
		// it was an empty line
	}

	// If the line set a texture
	else if (line_is_texture_path(split))
	{
		set_value();
	}

	// If the line define the map
	else if (line_is_map(split))
	{
		get_map();
	}

	// If it's not a texture's path and not define map
	else
	{
		error();
	}
}
```
