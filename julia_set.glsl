uniform vec2 resolution; // Résolution de la fenêtre
uniform float zoom; // Facteur de zoom
uniform vec2 offset; // Décalage pour centrer la fractale
uniform vec2 juliaC; // Constante complexe pour l'ensemble de Julia

void main()
{
    // Convertir les coordonnées du pixel en coordonnées complexes
    vec2 uv = (gl_FragCoord.xy / resolution) * zoom + offset;
    vec2 z = uv;
    float i;

    // Itérer sur les coordonnées complexes pour déterminer si le point fait partie de l'ensemble de Julia
    for (i = 0.0; i < 100.0; ++i)
    {
        z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + juliaC;

        // Si la magnitude du complexe dépasse 4, le point n'appartient pas à l'ensemble de Julia
        if (dot(z, z) > 4.0)
            break;
    }

    // Calculer la couleur en fonction du nombre d'itérations
    float color = i / 100.0;
    // Définir la couleur du fragment (pixel) avec la couleur calculée
    gl_FragColor = vec4(vec3(color), 1.0);
}