class CClientEntityList
{
public:

	CBaseEntity* GetClientEntity( int Index )
	{
		typedef CBaseEntity*(__thiscall* Fn)(void*, int);
		return getvfunc<Fn>(this, 3)(this, Index);
	}

	int GetHighestEntityIndex()
	{
		typedef int(__thiscall* Fn)(void*);
		return getvfunc<Fn>(this, 8)(this);
	}

	CBaseEntity* GetClientEntityFromHandle( HANDLE Handle )
	{
		typedef CBaseEntity*(__thiscall* Fn)(void*,HANDLE);
		return getvfunc<Fn>(this, 7)(this, Handle);
	}
	CBaseEntity *	GetClientEntityFromHandle(ULONG hEnt)
	{
		typedef CBaseEntity*(__thiscall* Fn)(void*, ULONG);
		return getvfunc<Fn>(this, 4)(this, hEnt);
	}
	CBaseEntity *	GetClientEntityFromHandle_D(DWORD hEnt)
	{
		typedef CBaseEntity*(__thiscall* Fn)(void*, int);
		return getvfunc<Fn>(this, 4)(this, hEnt);
	}

};

#define TE_BEAMPOINTS 0		// beam effect between two points


class C_Beam;
class Beam_t;

struct BeamInfo_t
{
	int			m_nType;

	// Entities
	CBaseEntity* m_pStartEnt;
	int			m_nStartAttachment;
	CBaseEntity* m_pEndEnt;
	int			m_nEndAttachment;

	// Points
	Vector		m_vecStart;
	Vector		m_vecEnd;

	int			m_nModelIndex;
	const char	*m_pszModelName;

	int			m_nHaloIndex;
	const char	*m_pszHaloName;
	float		m_flHaloScale;

	float		m_flLife;
	float		m_flWidth;
	float		m_flEndWidth;
	float		m_flFadeLength;
	float		m_flAmplitude;

	float		m_flBrightness;
	float		m_flSpeed;

	int			m_nStartFrame;
	float		m_flFrameRate;

	float		m_flRed;
	float		m_flGreen;
	float		m_flBlue;

	bool		m_bRenderable;

	int			m_nSegments;

	int			m_nFlags;

	// Rings
	Vector		m_vecCenter;
	float		m_flStartRadius;
	float		m_flEndRadius;

	BeamInfo_t()
	{
		m_nType = TE_BEAMPOINTS;
		m_nSegments = -1;
		m_pszModelName = NULL;
		m_pszHaloName = NULL;
		m_nModelIndex = -1;
		m_nHaloIndex = -1;
		m_bRenderable = true;
		m_nFlags = 0;
	}
};

class ITraceFilter;
class ITexture;

class IViewRenderBeams
{
public:
	// Construction
public:
	IViewRenderBeams(void);
	virtual				~IViewRenderBeams(void);

	// Implement IViewRenderBeams
public:
	virtual	void		InitBeams(void);
	virtual	void		ShutdownBeams(void);
	virtual	void		ClearBeams(void);

	// Updates the state of the temp ent beams
	virtual void		UpdateTempEntBeams();

	virtual void		DrawBeam(Beam_t *pbeam);
	virtual void		DrawBeam(C_Beam* pbeam, ITraceFilter *pEntityBeamTraceFilter = NULL);

	virtual	void		KillDeadBeams(CBaseEntity *pDeadEntity);

	virtual	void		CreateBeamEnts(int startEnt, int endEnt, int modelIndex, int haloIndex, float haloScale,
		float life, float width, float endWidth, float fadeLength, float amplitude,
		float brightness, float speed, int startFrame,
		float framerate, float r, float g, float b, int type = -1);
	virtual Beam_t		*CreateBeamEnts(BeamInfo_t &beamInfo);

	virtual	void		CreateBeamEntPoint(int	nStartEntity, const Vector *pStart, int nEndEntity, const Vector* pEnd,
		int modelIndex, int haloIndex, float haloScale,
		float life, float width, float endWidth, float fadeLength, float amplitude,
		float brightness, float speed, int startFrame,
		float framerate, float r, float g, float b);
	virtual Beam_t		*CreateBeamEntPoint(BeamInfo_t &beamInfo);

	virtual	void		CreateBeamPoints(Vector& start, Vector& end, int modelIndex, int haloIndex, float haloScale,
		float life, float width, float endWidth, float fadeLength, float amplitude,
		float brightness, float speed, int startFrame,
		float framerate, float r, float g, float b);
	virtual	Beam_t		*CreateBeamPoints(BeamInfo_t &beamInfo);

	virtual	void		CreateBeamRing(int startEnt, int endEnt, int modelIndex, int haloIndex, float haloScale,
		float life, float width, float endWidth, float fadeLength, float amplitude,
		float brightness, float speed, int startFrame,
		float framerate, float r, float g, float b, int flags);
	virtual Beam_t		*CreateBeamRing(BeamInfo_t &beamInfo);

	virtual void		CreateBeamRingPoint(const Vector& center, float start_radius, float end_radius, int modelIndex, int haloIndex, float haloScale,
		float life, float width, float m_nEndWidth, float m_nFadeLength, float amplitude,
		float brightness, float speed, int startFrame,
		float framerate, float r, float g, float b, int flags);
	virtual Beam_t		*CreateBeamRingPoint(BeamInfo_t &beamInfo);

	virtual	void		CreateBeamCirclePoints(int type, Vector& start, Vector& end,
		int modelIndex, int haloIndex, float haloScale, float life, float width,
		float endWidth, float fadeLength, float amplitude, float brightness, float speed,
		int startFrame, float framerate, float r, float g, float b);
	virtual Beam_t		*CreateBeamCirclePoints(BeamInfo_t &beamInfo);

	virtual	void		CreateBeamFollow(int startEnt, int modelIndex, int haloIndex, float haloScale,
		float life, float width, float endWidth, float fadeLength, float r, float g, float b,
		float brightness);
	virtual Beam_t		*CreateBeamFollow(BeamInfo_t &beamInfo);
	/*virtual void	InitBeams(void) = 0;
	virtual void	ShutdownBeams(void) = 0;
	virtual void	ClearBeams(void) = 0;

	// Updates the state of the temp ent beams
	virtual void	UpdateTempEntBeams() = 0;

	virtual void	DrawBeam(C_Beam* pbeam, ITraceFilter *pEntityBeamTraceFilter = NULL) = 0;
	virtual void	DrawBeam(Beam_t *pbeam) = 0;

	virtual void	KillDeadBeams(IClientEntity* pEnt) = 0;

	// New interfaces!
	virtual Beam_t	*CreateBeamEnts(BeamInfo_t &beamInfo) = 0;
	virtual Beam_t	*CreateBeamEntPoint(BeamInfo_t &beamInfo) = 0;
	virtual	Beam_t	*CreateBeamPoints(BeamInfo_t &beamInfo) = 0;
	virtual Beam_t	*CreateBeamRing(BeamInfo_t &beamInfo) = 0;
	virtual Beam_t	*CreateBeamRingPoint(BeamInfo_t &beamInfo) = 0;
	virtual Beam_t	*CreateBeamCirclePoints(BeamInfo_t &beamInfo) = 0;
	virtual Beam_t	*CreateBeamFollow(BeamInfo_t &beamInfo) = 0;

	virtual void	FreeBeam(Beam_t *pBeam) = 0;
	virtual void	UpdateBeamInfo(Beam_t *pBeam, BeamInfo_t &beamInfo) = 0;*/
};

enum DrawFlags_t
{
	DF_RENDER_REFRACTION = 0x1,
	DF_RENDER_REFLECTION = 0x2,

	DF_CLIP_Z = 0x4,
	DF_CLIP_BELOW = 0x8,

	DF_RENDER_UNDERWATER = 0x10,
	DF_RENDER_ABOVEWATER = 0x20,
	DF_RENDER_WATER = 0x40,

	DF_UNUSED1 = 0x100,
	DF_WATERHEIGHT = 0x200,
	DF_UNUSED2 = 0x400,
	DF_DRAWSKYBOX = 0x800,

	DF_FUDGE_UP = 0x1000,

	DF_DRAW_ENTITITES = 0x2000,

	DF_SKIP_WORLD = 0x4000,
	DF_SKIP_WORLD_DECALS_AND_OVERLAYS = 0x8000,

	DF_UNUSED5 = 0x10000,
	DF_SAVEGAMESCREENSHOT = 0x20000,
	DF_CLIP_SKYBOX = 0x40000,

	DF_SHADOW_DEPTH_MAP = 0x100000	// Currently rendering a shadow depth map
};


struct vrect_t;
class VPlane;

enum ClearFlags_t
{
	VIEW_CLEAR_COLOR = 0x1,
	VIEW_CLEAR_DEPTH = 0x2,
	VIEW_CLEAR_FULL_TARGET = 0x4,
	VIEW_NO_DRAW = 0x8,
	VIEW_CLEAR_OBEY_STENCIL = 0x10, // Draws a quad allowing stencil test to clear through portals
	VIEW_CLEAR_STENCIL = 0x20,
};

enum RenderViewInfo_t
{
	RENDERVIEW_UNSPECIFIED = 0,
	RENDERVIEW_DRAWVIEWMODEL = (1 << 0),
	RENDERVIEW_DRAWHUD = (1 << 1),
	RENDERVIEW_SUPPRESSMONITORRENDERING = (1 << 2),
};


class IViewRender
{
public:
	// SETUP
	// Initialize view renderer
	virtual void		Init(void) = 0;

	// Clear any systems between levels
	virtual void		LevelInit(void) = 0;
	virtual void		LevelShutdown(void) = 0;

	// Shutdown
	virtual void		Shutdown(void) = 0;

	// RENDERING
	// Called right before simulation. It must setup the view model origins and angles here so 
	// the correct attachment points can be used during simulation.	
	virtual void		OnRenderStart() = 0;

	// Called to render the entire scene
	virtual	void		Render(vrect_t *rect) = 0;

	// Called to render just a particular setup ( for timerefresh and envmap creation )
	// First argument is 3d view setup, second is for the HUD (in most cases these are ==, but in split screen the client .dll handles this differently)
	virtual void		RenderView(const CViewSetup &view, const CViewSetup &hudViewSetup, int nClearFlags, int whatToDraw) = 0;

	// What are we currently rendering? Returns a combination of DF_ flags.
	virtual int GetDrawFlags() = 0;

	// MISC
	// Start and stop pitch drifting logic
	virtual void		StartPitchDrift(void) = 0;
	virtual void		StopPitchDrift(void) = 0;

	// This can only be called during rendering (while within RenderView).
	virtual VPlane*		GetFrustum() = 0;

	virtual bool		ShouldDrawBrushModels(void) = 0;

	virtual const CViewSetup *GetPlayerViewSetup(int nSlot = -1) const = 0;
	virtual const CViewSetup *GetViewSetup(void) const = 0;

	virtual void		DisableVis(void) = 0;

	virtual int			BuildWorldListsNumber() const = 0;

	virtual void		SetCheapWaterStartDistance(float flCheapWaterStartDistance) = 0;
	virtual void		SetCheapWaterEndDistance(float flCheapWaterEndDistance) = 0;

	virtual void		GetWaterLODParams(float &flCheapWaterStartDistance, float &flCheapWaterEndDistance) = 0;

	virtual void		DriftPitch(void) = 0;

	virtual void		SetScreenOverlayMaterial(IMaterial *pMaterial) = 0;
	virtual IMaterial	*GetScreenOverlayMaterial() = 0;

	virtual void		WriteSaveGameScreenshot(const char *pFilename) = 0;
	virtual void		WriteSaveGameScreenshotOfSize(const char *pFilename, int width, int height) = 0;

	// Draws another rendering over the top of the screen
	virtual void		QueueOverlayRenderView(const CViewSetup &view, int nClearFlags, int whatToDraw) = 0;

	// Returns znear and zfar
	virtual float		GetZNear() = 0;
	virtual float		GetZFar() = 0;

	virtual void		GetScreenFadeDistances(float *min, float *max) = 0;
	virtual bool		AllowScreenspaceFade(void) = 0;

	virtual CBaseEntity *GetCurrentlyDrawingEntity() = 0;
	virtual void		SetCurrentlyDrawingEntity(CBaseEntity *pEnt) = 0;

	virtual bool		UpdateShadowDepthTexture(ITexture *pRenderTarget, ITexture *pDepthTexture, const CViewSetup &shadowView) = 0;

	virtual void		FreezeFrame(float flFreezeTime) = 0;

	virtual void		InitFadeData(void) = 0;
};